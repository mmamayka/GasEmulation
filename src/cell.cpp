#include "cell.hpp"

#include "collision.hpp"
#include "iacaMarks.h"
#include <algorithm>

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

	void Cell::update(double dt, ContainerCollider collider) noexcept {
		volatile char unused[56];
		(void)unused;

		__m256d dtvec = _mm256_broadcast_sd(&dt);
		Math::Vec4d sizevec = collider.size();
		Math::Vec4d msizevec = -sizevec;
		Math::Vec4d rvec(R);

		Math::Vec4d* end_pos = units_pos_ + count_;
		Math::Vec4d* unit_pos = units_pos_;
		Math::Vec4d* unit_vel = units_vel_;

		for(; unit_pos < (Math::Vec4d*)((size_t)end_pos & ~(size_t)1); 
				unit_pos += 2, unit_vel += 2) {
			_mm_prefetch(unit_pos + 2, _MM_HINT_NTA);
			_mm_prefetch(unit_vel + 2, _MM_HINT_NTA);

			// Math::Vec4d* next_pos = unit_pos + 2;
			// Math::Vec4d* next_vel = unit_vel + 2;

			// _mm_prefetch(next_pos, _MM_HINT_NTA);
			// _mm_prefetch(next_vel, _MM_HINT_NTA);
			
			__m256d unit1_posvec = (unit_pos + 0)->vector;
			__m256d unit1_velvec = (unit_vel + 0)->vector;

			__m256d unit1_newposvec = _mm256_fmadd_pd(unit1_velvec, dtvec, 
				unit1_posvec);

			__m256d unit1_npvpr = _mm256_add_pd(unit1_newposvec, rvec.vector);
			__m256d unit1_npvmr = _mm256_sub_pd(unit1_newposvec, rvec.vector);

			__m256d unit1_cmpvec1 = _mm256_cmp_pd(unit1_npvpr, sizevec.vector, 
				_CMP_GT_OQ);

			__m256d unit1_cmpvec2 = _mm256_cmp_pd(unit1_npvmr, msizevec.vector,
				_CMP_LT_OQ);

			int unit1_mask1 = _mm256_movemask_pd(unit1_cmpvec1);

			int unit1_mask2 = _mm256_movemask_pd(unit1_cmpvec2);

			int mask1 = unit1_mask1 | (unit1_mask2 << 4);

			(unit_pos + 0)->vector = unit1_newposvec;

			if(mask1) {
				ResolveCollision(*(unit_pos + 0), *(unit_vel + 0), collider, mask1);
			}

			__m256d unit2_posvec = (unit_pos + 1)->vector;
			__m256d unit2_velvec = (unit_vel + 1)->vector;


			__m256d unit2_newposvec = _mm256_fmadd_pd(unit2_velvec, dtvec, 
			 	unit2_posvec);

			int mask2 =
				_mm256_movemask_pd(
					_mm256_cmp_pd(_mm256_add_pd(unit2_newposvec, rvec.vector),
								  sizevec.vector, _CMP_GT_OQ)
								  ) 
				|
				(_mm256_movemask_pd(
					_mm256_cmp_pd(_mm256_sub_pd(unit2_newposvec, rvec.vector),
								  msizevec.vector, _CMP_LT_OQ))
					<< 4);


			(unit_pos + 1)->vector = unit2_newposvec;

			if(mask2) {
				ResolveCollision(*(unit_pos + 1), *(unit_vel + 1), collider, mask2);
			}

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
		for(Math::Vec4d *this_pos = units_pos_; this_pos < this_pos_end; ++this_pos) {
			int mask;
			if(HasCollision(*this_pos, collider, mask)) {
				Math::Vec4d* this_vel = units_vel_ + (this_pos - units_pos_);
				ResolveCollision(*this_pos, *this_vel, collider, mask);
			}


		}
	}

	void Cell::collideWith(Cell& other_cell) noexcept {
		volatile char unused[56];
		(void)unused;
		if(&other_cell != this) {
			Math::Vec4d* this_pos_end = this->units_pos_ + this->count_;
			Math::Vec4d* other_pos_end = other_cell.units_pos_ + other_cell.count_;

			for(Math::Vec4d *this_pos = units_pos_; this_pos < this_pos_end; ++this_pos)

				for(Math::Vec4d *other_pos = other_cell.units_pos_;
						other_pos < other_pos_end; ++other_pos) 
				{
					double d2;
					Math::Vec4d dr;


					if(HasCollision(*this_pos, *other_pos, d2, dr)) {
						Math::Vec4d* this_vel = this_pos - this->units_pos_ +
							this->units_vel_;

						Math::Vec4d* other_vel = other_pos - other_cell.units_pos_ + 
							other_cell.units_vel_;

						ResolveCollision(*this_pos, *this_vel, *other_pos, *other_vel,
							d2, dr);
					}
					 // _mm_prefetch(other_pos + 1, _MM_HINT_T1);
				}
		}
		else {
			Math::Vec4d* this_pos_end = units_pos_ + count_;
			for(Math::Vec4d *pos1 = units_pos_; pos1 < this_pos_end; ++pos1)
				for(Math::Vec4d *pos2 = pos1 + 1; pos2 < this_pos_end; ++pos2) {
					double d2;
					Math::Vec4d dr;
					if(HasCollision(*pos1, *pos2, d2, dr)) {
						Math::Vec4d* vel1 = pos1 - units_pos_ + units_vel_;
						Math::Vec4d* vel2 = pos2 - units_pos_ + units_vel_;

						ResolveCollision(*pos1, *vel1, *pos2, *vel2, d2, dr);
					}
					// _mm_prefetch(pos2 + 1, _MM_HINT_T1);
				}
		}
	}


}
