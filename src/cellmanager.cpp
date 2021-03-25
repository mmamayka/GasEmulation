#include "cellmanager.hpp"
#include "math.hpp"

namespace Phys {
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

}
