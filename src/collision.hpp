#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

#include "math.hpp"
#include "gasunit.hpp"
#include "debug.hpp"

namespace Phys {
	class ContainerCollider {
	public:
		ContainerCollider(double width, double height, double depth) noexcept :
			size_(width, height, depth) {}

		Math::Vec4d const size() const noexcept { return size_; }
		Math::Vec4d& size() noexcept { return size_; }

	private:
		Math::Vec4d size_;
	};

	class CellIterator {
	public:
		GasUnit& operator* () noexcept { return *pos_; }
		GasUnit const& operator* () const noexcept { return *pos_; }

		GasUnit* operator->() noexcept { return pos_; }
		GasUnit const* operator->() const noexcept { return pos_; }

		CellIterator operator++() noexcept 
		{ 
			return CellIterator(++pos_);
		}

		void erase() noexcept { pos_->pos().x = NAN; }

	protected:
		friend class Cell;
		CellIterator(GasUnit* pos) noexcept : pos_(pos) {}

	private:
		GasUnit* pos_;
	};

	inline bool operator!= (CellIterator a, CellIterator b) noexcept
	{ return &*a != &*b; }

	class Cell {
	public:
		Cell(size_t initial_capacity = 4);
		~Cell() noexcept;

		Cell(Cell const&) = delete;
		Cell operator= (Cell const&) = delete;

		void push(GasUnit unit);
		void fit() noexcept;

		void update(double dt) noexcept;
		void collideWith(ContainerCollider collider) noexcept;
		void collideWith(Cell& other_cell) noexcept;

		bool ok() {
			for(size_t i = 0; i < count_; ++i)
				if(std::isnan(units_[i].pos().x))
					return false;
			return true;
		}

		size_t count() const noexcept { return count_; }

		CellIterator begin() noexcept 
		{ return CellIterator(units_); }

		CellIterator end() noexcept 
		{ return CellIterator(units_ + count_); }

	private:
		GasUnit* units_;
		size_t count_;
		size_t capacity_;
	};

	class CellManager {
	public:
		CellManager(double width, double height, double depth, double cell_size,
			GasUnit units[], size_t count);

		CellManager(CellManager&) = delete;
		CellManager operator= (CellManager&) = delete;

		void update(double dt);

		void asrt() {
			for(size_t i = 0; i < cells_count_; ++i)
				ASSERT(cells_[i].ok());
		}

		size_t getNumCellsX() const noexcept { return ncellsx_; }
		size_t getNumCellsY() const noexcept { return ncellsy_; }
		size_t getNumCellsZ() const noexcept { return ncellsz_; }
		size_t getCountAt(size_t x, size_t y, size_t z)
		{ return cells_[x * (ncellsz_ * ncellsy_) + y * ncellsz_ + z].count(); }

	private:
		size_t getCellIndex(Math::Vec4d pos) const noexcept;

		size_t ncellsx_;
		size_t ncellsy_;
		size_t ncellsz_;
		size_t cells_count_;

		double width_;
		double height_;
		double depth_;
		double cell_size_;

		std::vector<Cell> cells_;
		ContainerCollider container_;
	};

	bool ResolveCollision(GasUnit& a, GasUnit& b) noexcept;
	bool ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept;
}

#endif
