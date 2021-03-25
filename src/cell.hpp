#ifndef CELL_H
#define CELL_H

#include "math.hpp"
#include "containercollider.hpp"
#include "gasunit.hpp"

namespace Phys {
	class CellIterator {
	public:
		Math::Vec4d& pos() noexcept { return *pos_; };
		Math::Vec4d const& pos() const noexcept { return *pos_; };

		Math::Vec4d& vel() noexcept { return *vel_; };
		Math::Vec4d const& vel() const noexcept { return *vel_; };

		CellIterator operator++() noexcept { return CellIterator(++pos_, ++vel_); }

		void erase() noexcept { pos_->x = NAN; }

	private:
		friend class Cell;
		CellIterator(Math::Vec4d* pos, Math::Vec4d* vel) noexcept : 
			pos_(pos), vel_(vel) {}

		Math::Vec4d* pos_;
		Math::Vec4d* vel_;
	};

	inline bool operator!= (CellIterator const& a, CellIterator const& b)
	{ return &a.pos() != &b.pos(); }

	class Cell {
	public:
		Cell(size_t initial_capacity = 4);
		~Cell() noexcept;

		Cell(Cell const&) = delete;
		Cell operator= (Cell const&) = delete;

		void push(GasUnit unit) { this->push(unit.pos(), unit.vel()); }
		void push(Math::Vec4d pos, Math::Vec4d vel);
		void fit() noexcept;

		void update(double dt) noexcept;
		void collideWith(ContainerCollider collider) noexcept;
		void collideWith(Cell& other_cell) noexcept;

		size_t count() const noexcept { return count_; }

		CellIterator begin() noexcept 
		{ return CellIterator(units_pos_, units_vel_); }

		CellIterator end() noexcept 
		{ return CellIterator(units_pos_ + count_, NULL); }

	private:
		Math::Vec4d* units_pos_;
		Math::Vec4d* units_vel_;

		size_t count_;
		size_t capacity_;
	};

}

#endif
