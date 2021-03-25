#include <cstdlib>
#include <iostream>
#include <utility>
#include <cassert>
#include <algorithm>
#include "collision.hpp"
#include "debug.hpp"
#include "iacaMarks.h"

namespace Phys {
	Cell::Cell(size_t initial_capacity) :
		//units_(new GasUnit[initial_capacity]),
		units_pos_((Math::Vec4d*)_mm_malloc(sizeof(Math::Vec4d) * initial_capacity, 64)),
		units_vel_((Math::Vec4d*)_mm_malloc(sizeof(Math::Vec4d) * initial_capacity, 64)),
		count_(0),
		capacity_(initial_capacity)
	{}
	
	Cell::~Cell() noexcept {
		// delete[] units_;
		_mm_free(units_pos_);
		_mm_free(units_vel_);
	}

	void Cell::push(Math::Vec4d pos, Math::Vec4d vel) {
		if(count_ == capacity_) {
			size_t new_capacity = capacity_ * 2;
			//GasUnit* new_units = new GasUnit[new_capacity];
			Math::Vec4d* new_units_pos = (Math::Vec4d*)_mm_malloc(
				sizeof(Math::Vec4d) * new_capacity, 64);
			Math::Vec4d* new_units_vel = (Math::Vec4d*)_mm_malloc(
				sizeof(Math::Vec4d) * new_capacity, 64);

			std::copy_n(units_pos_, new_capacity, new_units_pos);
			std::copy_n(units_vel_, new_capacity, new_units_vel);

			//delete[] units_;
			_mm_free(units_pos_);
			_mm_free(units_vel_);

			capacity_ = new_capacity;
			units_pos_ = new_units_pos;
			units_vel_ = new_units_vel;
		}

		units_pos_[count_] = pos;
		units_vel_[count_] = vel;
		++count_;
	}

	void Cell::fit() noexcept {
		Math::Vec4d* invalid_pos = units_pos_;
		Math::Vec4d* end_pos = units_pos_ + count_;

		while(invalid_pos < end_pos && std::isfinite(invalid_pos->x))
			++invalid_pos;

		Math::Vec4d* invalid_vel = invalid_pos - units_pos_ + units_vel_;

		Math::Vec4d* valid_pos = invalid_pos + 1;
		Math::Vec4d* valid_vel = invalid_vel + 1;

		while(valid_pos < end_pos) {
			if(std::isfinite(valid_pos->x)) {
				*invalid_pos = *valid_pos;
				*invalid_vel = *valid_vel;

				++invalid_pos;
				++invalid_vel;
			}

			++valid_pos;
			++valid_vel;
		}

		count_ = invalid_pos - units_pos_;
	}

	void Cell::update(double dt) noexcept {
		__m256d dtvec = _mm256_broadcast_sd(&dt);

		Math::Vec4d* end_pos = units_pos_ + count_;
		Math::Vec4d* unit_pos = units_pos_;
		Math::Vec4d* unit_vel = units_vel_;

		for(; unit_pos < (Math::Vec4d*)((size_t)end_pos & ~(size_t)1); 
				unit_pos += 2, unit_vel += 2) {
			
			__m256d unit1_posvec = (unit_pos + 0)->vector;
			__m256d unit1_velvec = (unit_vel + 0)->vector;

			__m256d unit2_posvec = (unit_pos + 1)->vector;
			__m256d unit2_velvec = (unit_vel + 1)->vector;

			__m256d unit1_newposvec = _mm256_fmadd_pd(unit1_velvec, dtvec, 
				unit1_posvec);

			__m256d unit2_newposvec = _mm256_fmadd_pd(unit2_velvec, dtvec, 
			 	unit2_posvec);

			(unit_pos + 0)->vector = unit1_newposvec;
			(unit_pos + 1)->vector = unit2_newposvec;

		}

		for(; unit_pos < end_pos; ++unit_pos, ++unit_vel) {
			__m256d unit_posvec = unit_pos->vector;
			__m256d unit_velvec = unit_vel->vector;

			__m256d unit_newposvec = _mm256_fmadd_pd(unit_velvec, dtvec, unit_posvec);

			unit_pos->vector = unit_newposvec;
		}
	}

	void Cell::collideWith(ContainerCollider collider) noexcept {
		Math::Vec4d* this_pos_end = units_pos_ + count_;
		for(Math::Vec4d *this_pos = units_pos_, *this_vel = units_vel_;
				this_pos < this_pos_end; ++this_pos, ++this_vel)
			ResolveCollision(*this_pos, *this_vel, collider);
	}

	void Cell::collideWith(Cell& other_cell) noexcept {
		if(&other_cell != this) {
			Math::Vec4d* this_pos_end = this->units_pos_ + this->count_;
			Math::Vec4d* other_pos_end = other_cell.units_pos_ + other_cell.count_;

			for(Math::Vec4d *this_pos = units_pos_; this_pos < this_pos_end; ++this_pos)

				for(Math::Vec4d *other_pos = other_cell.units_pos_;
						other_pos < other_pos_end; ++other_pos) 
				{
					double d2;
					Math::Vec4d dr;

					_mm_prefetch(other_pos + 1, _MM_HINT_T1);

					if(HasCollision(*this_pos, *other_pos, d2, dr)) {
						Math::Vec4d* this_vel = this_pos - this->units_pos_ +
							this->units_vel_;

						Math::Vec4d* other_vel = other_pos - other_cell.units_pos_ + 
							other_cell.units_vel_;

						ResolveCollision(*this_pos, *this_vel, *other_pos, *other_vel,
							d2, dr);
					}
				}
		}
		else {
			Math::Vec4d* this_pos_end = units_pos_ + count_;
			for(Math::Vec4d *pos1 = units_pos_; pos1 < this_pos_end; ++pos1)
				for(Math::Vec4d *pos2 = pos1 + 1; pos2 < this_pos_end; ++pos2) {
					double d2;
					Math::Vec4d dr;
					_mm_prefetch(pos2 + 1, _MM_HINT_T1);
					if(HasCollision(*pos1, *pos2, d2, dr)) {
						Math::Vec4d* vel1 = pos1 - units_pos_ + units_vel_;
						Math::Vec4d* vel2 = pos2 - units_pos_ + units_vel_;

						ResolveCollision(*pos1, *vel1, *pos2, *vel2, d2, dr);
					}
				}
		}
	}

	CellManager::CellManager(double width, double height, 
		double depth, double r, GasUnit units[], size_t count) :

		ncellsx_((size_t)(2.0 * width / r)),
		ncellsy_((size_t)(2.0 * height / r)),
		ncellsz_((size_t)(2.0 * depth / r)),
		cells_count_(ncellsx_ * ncellsy_ * ncellsz_),

		width_(width),
		height_(height),
		depth_(depth),
		cell_size_(r),

		cells_(cells_count_),
		container_(width, height, depth)
	{
		for(GasUnit* unit = units; unit < units + count; ++unit) {
			cells_[this->getCellIndex(unit->pos())].push(*unit);
		}
	}

	void CellManager::update(double dt) {
		this->move(dt);
		this->updateCells();
		this->intersect();
	}

	void CellManager::move(double dt) noexcept {
		/*for(size_t i = 0; i < cells_.size(); ++i) {
			cells_[i].update(dt);
			cells_[i].collideWith(container_);
		}
		*/

		Cell* end = cells_.data() + cells_.size();
		for(Cell* cell = cells_.data(); cell < end; ++cell) {
			cell->update(dt);
			cell->collideWith(container_);
		}
	}
	void CellManager::updateCells() {
		for(size_t ncell = 0; ncell < cells_count_; ++ncell) {
			for(CellIterator itr = cells_[ncell].begin(); itr != cells_[ncell].end();
				++itr)
			{
				size_t new_index = getCellIndex(itr.pos());
				if(new_index != ncell) {
					cells_[new_index].push(itr.pos(), itr.vel());
					// bad_units.push_back(std::make_pair(new_index, *itr));
					itr.erase();
					++move_count_;
				}
			}

			cells_[ncell].fit();
		}
	}

	void CellManager::intersect() noexcept {
		for(size_t cx = 0; cx < ncellsx_; ++cx) {
			for(size_t cy = 0; cy < ncellsy_; ++cy) {
				for(size_t cz = 0; cz < ncellsz_; ++cz) {
					Cell& main =
						cells_[cx * (ncellsy_ * ncellsz_) + cy * ncellsz_ + cz];

					size_t xstart = cx == 0 ? 0 : cx - 1;
					size_t ystart = cy == 0 ? 0 : cy - 1;
					size_t zstart = cz == 0 ? 0 : cz - 1;

					size_t xend = cx == ncellsx_ - 1 ? ncellsx_ - 1 : cx;
					size_t yend = cy == ncellsy_ - 1 ? ncellsy_ - 1 : cy;
					size_t zend = cz == ncellsz_ - 1 ? ncellsz_ - 1 : cz;

					for(size_t cxx = xstart; cxx <= xend; ++cxx) {
						for(size_t cyy = ystart; cyy <= yend; ++cyy) {
							for(size_t czz = zstart; czz <= zend; ++czz) {
								Cell& cell =
									cells_[cxx * (ncellsy_ * ncellsz_) +
									cyy * ncellsz_ + czz];

								main.collideWith(cell);
							}
						}
					}
				}
			}
		}

	}

	size_t CellManager::getCellIndex(Math::Vec4d pos) const noexcept {
		Math::Vec4d rind = (pos + Math::Vec4d(width_, height_, depth_)) / cell_size_;

		for(size_t i = 0; i < 4; ++i) {
			if(rind.data[i] < 0.0) rind.data[i] = 0.0;
		}

		size_t x = rind.x;
		size_t y = rind.y;
		size_t z = rind.z;

		if(x >= ncellsx_) x = ncellsx_ - 1;
		if(y >= ncellsy_) y = ncellsy_ - 1;
		if(z >= ncellsz_) z = ncellsz_ - 1;

		return x * (ncellsy_ * ncellsz_) + y * ncellsz_ + z;
	}

	bool HasCollision(Math::Vec4d apos, Math::Vec4d bpos, double& d2, Math::Vec4d& dr)
		noexcept
	{
		using namespace Math;

		dr = apos - bpos;
		d2 = dr.sqlen();

		return (d2 < D2);
	}

	void ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, Math::Vec4d& bpos, 
		Math::Vec4d& bvel, double& d2, Math::Vec4d& dr) noexcept
	{
		using namespace Math;

		Vec4d dv = avel - bvel;


		// At^2 -2Bt + C = 0
		double A = dv.sqlen();

		if(AboutZero(A)) { [[unlikely]]
			return;
		}
		else {
			double Bhalf = Dot(dv, dr);
			double C = d2 - D2;
			double dt = NAN;
			double Dby4 = Bhalf * Bhalf - A * C;
			double D = Sqrt(Dby4);

			if(Bhalf > 0.0) {
				Bhalf = -Bhalf;
			}
			dt = (Bhalf + D) / A;

			apos -= avel * dt;
			bpos -= bvel * dt;

			Vec4d new_dr = apos - bpos;
			Vec4d new_dv = new_dr * Dot(dv, new_dr) / new_dr.sqlen();

			avel -= new_dv;
			bvel += new_dv;

			apos += avel * dt;
			bpos += bvel * dt;

		}
	}

	bool ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, 
			ContainerCollider const& b) noexcept 
	{
		using namespace Math;

		Vec4d Rvec(R);

		int cmask = 
			_mm256_movemask_pd(
				_mm256_cmp_pd((apos + Rvec).vector, b.size().vector, _CMP_GT_OQ)) |
			(_mm256_movemask_pd(
				_mm256_cmp_pd((apos - Rvec).vector, (-b.size()).vector, _CMP_LT_OQ))
			 	<< 4);

		// int cmask = (CMPGTMask(apos + Rvec, b.size()) | 
			// (CMPLTMask(apos - Rvec, -b.size()) << 4));

		if(!cmask) { [[likely]]
			return false;
		}

		// rewrite using SSE and masking
		if(cmask & (1 << 0)) {
			avel.x = -avel.x;
			apos.x -= 2 * (apos.x + R - b.size().x);
		}
		if(cmask & (1 << 1)) {
			avel.y = -avel.y;
			apos.y -= 2 * (apos.y + R - b.size().y);
		}
		if(cmask & (1 << 2)) {
			avel.z = -avel.z;
			apos.z -= 2 * (apos.z + R - b.size().z);
		}

		if(cmask & (1 << 4)) {
			avel.x = -avel.x;
			apos.x += 2 * (-apos.x - b.size().x + R);
		}
		if(cmask & (1 << 5)) {
			avel.y = -avel.y;
			apos.y += 2 * (-apos.y - b.size().y + R);
		}
		if(cmask & (1 << 6)) {
			avel.z = -avel.z;
			apos.z += 2 * (-apos.z - b.size().z + R);
		}

		// std::cout << "detected" << std::endl;
		return true;
	}

}
