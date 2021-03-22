#include <cstdlib>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "collision.hpp"
#include "debug.hpp"

namespace Phys {
	Cell::Cell(size_t initial_capacity) :
		units_(new GasUnit[initial_capacity]),
		count_(0),
		capacity_(initial_capacity)
	{}
	
	Cell::~Cell() noexcept {
		delete[] units_;
	}

	void Cell::push(GasUnit unit) {
		if(count_ == capacity_) {
			size_t new_capacity = capacity_ * 2;
			GasUnit* new_units = new GasUnit[new_capacity];
			std::copy_n(units_, new_capacity, new_units);

			delete[] units_;

			capacity_ = new_capacity;
			units_ = new_units;
		}

		units_[count_++] = unit;
	}

	void Cell::fit() noexcept {
		GasUnit* invalid = units_;
		GasUnit* end = units_ + count_;

		while(invalid < end && std::isfinite(invalid->pos().x))
			++invalid;

		GasUnit* valid = invalid + 1;

		while(valid < end) {
			if(std::isfinite(valid->pos().x)) {
				*invalid = *valid;
				++invalid;
			}

			++valid;
		}

		count_ = invalid - units_;
	}

	void Cell::update(double dt) noexcept {
		for(auto& unit : *this) {
			assert(std::isfinite(unit.pos().x));
			assert(std::isfinite(unit.pos().y));
			assert(std::isfinite(unit.pos().z));
			assert(std::isfinite(unit.pos().w));

			unit.move(dt);
		}
	}

	void Cell::collideWith(ContainerCollider collider) noexcept {
		for(auto& unit : *this)
			ResolveCollision(unit, collider);
	}

	void Cell::collideWith(Cell& other_cell) noexcept {
		if(&other_cell != this) {
			for(auto& this_unit : *this)
				for(auto& other_unit : other_cell)
					ResolveCollision(this_unit, other_unit);
		}
		else {
			GasUnit* this_end = units_ + count_;
			for(GasUnit* unit1 = units_; unit1 < this_end; ++unit1)
				for(GasUnit* unit2 = unit1 + 1; unit2 < this_end; ++unit2)
					ResolveCollision(*unit1, *unit2);
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
		for(auto& cell : cells_) {
			cell.update(dt);
			cell.collideWith(container_);
		}

		for(size_t ncell = 0; ncell < cells_count_; ++ncell) {
			for(CellIterator itr = cells_[ncell].begin(); itr != cells_[ncell].end();
				++itr)
			{
				size_t new_index = getCellIndex(itr->pos());
				if(new_index != ncell) {
					cells_[new_index].push(*itr);
					itr.erase();
				}
			}

			cells_[ncell].fit();
		}

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

	bool ResolveCollision(GasUnit& a, GasUnit& b) noexcept {
		using namespace Math;

		Vec4d dr = a.pos() - b.pos();
		double d2 = dr.sqlen();

		if(d2 >= D2) { [[likely]]
			return false;
		}

		Vec4d dv = a.vel() - b.vel();


		// At^2 -2Bt + C = 0
		double A = dv.sqlen();

		if(AboutZero(A)) { [[unlikely]]
			return false;
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

			a.pos() -= a.vel() * dt;
			b.pos() -= b.vel() * dt;

			Vec4d new_dr = a.pos() - b.pos();
			Vec4d new_dv = new_dr * Dot(dv, new_dr) / new_dr.sqlen();

			a.vel() -= new_dv;
			b.vel() += new_dv;

			a.pos() += a.vel() * dt;
			b.pos() += b.vel() * dt;

		}
		return true;
	}

	bool ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept {
		using namespace Math;

		Vec4d Rvec(R);

		int cmask = 
			_mm256_movemask_pd(
				_mm256_cmp_pd((a.pos() + Rvec).vector, b.size().vector, _CMP_GT_OQ)) |
			(_mm256_movemask_pd(
				_mm256_cmp_pd((a.pos() - Rvec).vector, (-b.size()).vector, _CMP_LT_OQ))
			 	<< 4);

		// int cmask = (CMPGTMask(a.pos() + Rvec, b.size()) | 
			// (CMPLTMask(a.pos() - Rvec, -b.size()) << 4));

		if(!cmask) { [[likely]]
			return false;
		}

		// rewrite using SSE and masking
		if(cmask & (1 << 0)) {
			a.vel().x = -a.vel().x;
			a.pos().x -= 2 * (a.pos().x + R - b.size().x);
		}
		if(cmask & (1 << 1)) {
			a.vel().y = -a.vel().y;
			a.pos().y -= 2 * (a.pos().y + R - b.size().y);
		}
		if(cmask & (1 << 2)) {
			a.vel().z = -a.vel().z;
			a.pos().z -= 2 * (a.pos().z + R - b.size().z);
		}

		if(cmask & (1 << 4)) {
			a.vel().x = -a.vel().x;
			a.pos().x += 2 * (-a.pos().x - b.size().x + R);
		}
		if(cmask & (1 << 5)) {
			a.vel().y = -a.vel().y;
			a.pos().y += 2 * (-a.pos().y - b.size().y + R);
		}
		if(cmask & (1 << 6)) {
			a.vel().z = -a.vel().z;
			a.pos().z += 2 * (-a.pos().z - b.size().z + R);
		}

		// std::cout << "detected" << std::endl;
		return true;
	}

}
