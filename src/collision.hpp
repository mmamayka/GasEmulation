#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

#include "math.hpp"
#include "gasunit.hpp"

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

	class CollisionCellManager {
	public:
		CollisionCellManager(double width, double height, double depth, double r);
		CollisionCellManager(CollisionCellManager&) = delete;
		CollisionCellManager operator= (CollisionCellManager&) = delete;
		~CollisionCellManager();

		void registerUnits(std::vector<GasUnit>& units);
		void resolveCollisions() noexcept;
		size_t getUnitsCountAt(size_t cell_index);

	private:
		void collideCells(std::vector<GasUnit*>& c1, std::vector<GasUnit*>& c2);

		size_t ncellsx_;
		size_t ncellsy_;
		size_t ncellsz_;
		size_t cells_count_;

		double width_;
		double height_;
		double depth_;
		double cell_size_;

		std::vector<GasUnit*>* cells_;
		ContainerCollider container_;
	};

	bool ResolveCollision(GasUnit& a, GasUnit& b) noexcept;
	bool ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept;
}

#endif
