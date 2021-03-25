#ifndef CELL_MANAGER_H
#define CELL_MANAGER_H

#include <vector>
#include "containercollider.hpp"
#include "cell.hpp"

namespace Phys {
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

}

#endif
