#include "collision.hpp"
#include <iostream>

namespace Phys {
	CollisionCellManager::CollisionCellManager(double width, double height, 
		double depth, double r) :

		ncellsx_((size_t)(2.0 * width / r)),
		ncellsy_((size_t)(2.0 * height / r)),
		ncellsz_((size_t)(2.0 * depth / r)),
		cells_count_(ncellsx_ * ncellsy_ * ncellsz_),

		width_(width),
		height_(height),
		depth_(depth),
		cell_size_(r),

		cells_(new std::vector<GasUnit*>[cells_count_]),
		container_(width, height, depth)
	{}

	CollisionCellManager::~CollisionCellManager() {
		delete[] cells_;
	}

	void CollisionCellManager::registerUnits(std::vector<GasUnit>& units) {
		for(size_t i = 0; i < cells_count_; ++i)
			cells_[i].clear();

		for(auto& unit : units) {
			ResolveCollision(unit, container_);

			double rposx = (unit.pos().x + width_) / cell_size_;
			double rposy = (unit.pos().y + height_) / cell_size_;
			double rposz = (unit.pos().z + depth_) / cell_size_;

			size_t posx = (size_t)rposx;
			size_t posy = (size_t)rposy;
			size_t posz = (size_t)rposz;

			size_t index = posx * (ncellsz_ * ncellsy_) + posy * ncellsz_ + posz;
			cells_[index].push_back(&unit);
		}
	}

	void CollisionCellManager::resolveCollisions() noexcept {
		for(size_t cx = 0; cx < ncellsx_; ++cx) {
			for(size_t cy = 0; cy < ncellsy_; ++cy) {
				for(size_t cz = 0; cz < ncellsz_; ++cz) {
					std::vector<GasUnit*>& main = 
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
								std::vector<GasUnit*>& cell = 
									cells_[cxx * (ncellsy_ * ncellsz_) +
									cyy * ncellsz_ + czz];

								collideCells(main, cell);
							}
						}
					}



				}
			}
		}



	}

	void CollisionCellManager::collideCells(std::vector<GasUnit*>& c1, 
		std::vector<GasUnit*>& c2)
	{
		for(auto u1 : c1)
			for(auto u2 : c2) {
				if(u1 != u2) {
					ResolveCollision(*u1, *u2);
				}
			}
	}

	bool ResolveCollision(GasUnit& a, GasUnit& b) noexcept {
		using namespace Math;

		Vec4d dr = a.pos() - b.pos();

		// test for Axis Aligned Bound AABB collision
		/*
		if(!InfNormLessThan(Abs(dr), D)) { [[likely]]
			return false;
		}
		*/

		// test for circle collision
		double d2 = dr.sqlen();

		if(d2 >= D2) { [[likely]]
			return false;
		}

		Vec4d dv = a.vel() - b.vel();

		double dt = NAN;

		// At^2 -2Bt + C = 0
		double A = dv.sqlen();
		double Bhalf = Dot(dv, dr);
		double C = d2 - D2;

		if(AboutZero(A)) { [[unlikely]]
			return false;
		}
		else {
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
