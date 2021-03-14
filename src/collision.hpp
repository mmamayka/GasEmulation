#ifndef COLLISION_H
#define COLLISION_H

#include "math.hpp"
#include "gasunit.hpp"

namespace Phys {
	constexpr size_t CELLSTORAGE_CAPACITY = 16;

	class ContainerCollider {
	public:
		ContainerCollider(float width, float height, float depth) noexcept :
			size_(width, height, depth) {}

		Math::Vec4 const size() const noexcept { return size_; }
		Math::Vec4& size() noexcept { return size_; }

	private:
		Math::Vec4 size_;
	};

	/*
	struct CellStorage {
		GasUnit* units_[CELLSTORAGE_CAPACITY];
		CellStorage* next_;
	};

	class CellStoragePool {
	public:

	private:
	};

	class Cell {
	public:

	private:
		CellStorage main_storage_;
		CellStorage* last_storage_;
		size_t nfilled_cells_;
	};

	class CellManager {
	public:

	private:
		size_t width_;
		size_t height_;
		size_t depth_;
	};
	*/

	bool const ResolveCollision(GasUnit& a, GasUnit& b) noexcept;
	bool const ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept;
}

#endif
