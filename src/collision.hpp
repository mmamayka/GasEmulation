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

	class CellManager {
	public:
		CellManager(double width, double height, double depth, double cell_size,
			GasUnit units[], size_t count);

		CellManager(CellManager&) = delete;
		CellManager operator= (CellManager&) = delete;

		void update(double dt);

		size_t getNumCellsX() const noexcept { return ncellsx_; }
		size_t getNumCellsY() const noexcept { return ncellsy_; }
		size_t getNumCellsZ() const noexcept { return ncellsz_; }
		size_t getCountAt(size_t x, size_t y, size_t z) const noexcept
		{ return cells_[x * (ncellsz_ * ncellsy_) + y * ncellsz_ + z].count(); }

		double getWidth() const noexcept { return width_; }
		double getHeight() const noexcept { return height_; }
		double getDepth() const noexcept { return depth_; }

		double getCellSize() const noexcept { return cell_size_; }

	private:
		void move(double dt) noexcept;
		void updateCells();
		void intersect() noexcept;

		size_t getCellIndex(Math::Vec4d pos) const noexcept;

		size_t ncellsx_;
		size_t ncellsy_;
		size_t ncellsz_;
		size_t cells_count_;

		double width_;
		double height_;
		double depth_;
		double cell_size_;

		size_t move_count_;

		std::vector<Cell> cells_;
		ContainerCollider container_;
	};

	// bool ResolveCollision(GasUnit& a, GasUnit& b) noexcept;
	bool HasCollision(Math::Vec4d apos, Math::Vec4d bpos, double& d2, Math::Vec4d& dr)
		noexcept;

	__attribute__((noinline))
	void ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, Math::Vec4d& bpos, 
		Math::Vec4d& bvel, double& d2, Math::Vec4d& dr) noexcept;

	//__attribute__((noinline))
	// bool ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept;
	bool ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, 
			ContainerCollider const& b) noexcept;
}

#endif
