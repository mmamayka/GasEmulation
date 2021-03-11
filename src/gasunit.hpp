#ifndef GASUNIT_H
#define GASUNIT_H

#include "math.hpp"
#include <memory>

namespace Phys {
	constexpr float R = 2.f;
	constexpr float D = R * 2.f;
	constexpr float D2 = D * D;
	constexpr float M = 1.f;
	constexpr size_t COLLISIONCELL_CAPACITY = 4;

	class GasUnit;
	class CollisionCell;
	class CollisionCellStoragePool;
	class CollisionCellStorage;
	class ContainerCollider;
	class CollisionManager;

	class GasUnit {
	public:
		GasUnit(Math::Vec4 const& init_pos, Math::Vec4 const& init_vel) noexcept :
			pos_(init_pos), vel_(init_vel) {}

		inline Math::Vec4 const pos() const noexcept { return pos_; }
		inline Math::Vec4& pos() noexcept { return pos_; }

		inline Math::Vec4 const vel() const noexcept { return vel_; }
		inline Math::Vec4& vel() noexcept { return vel_; }

		void move(float dt) noexcept { pos_ += vel_ * dt; }

	private:
		Math::Vec4 pos_;
		Math::Vec4 vel_;
	};

	class ContainerCollider {
	public:
		ContainerCollider(float width, float height, float depth) noexcept :
			size_(width, height, depth) {}

		Math::Vec4 const size() const noexcept { return size_; }
		Math::Vec4& size() noexcept { return size_; }

	private:
		Math::Vec4 size_;
	};

	class CollisionData {};

	class CollisionCellStoragePool {
	public:
		CollisionCellStoragePool(size_t initial_total_count);
		~CollisionCellStoragePool() noexcept;

		void reset() noexcept { allocated_ = 0; }
		CollisionCellStorage* const getNext();

	private:
		CollisionCellStorage* cells_;
		size_t allocated_;
		size_t total_;
	};

	class CollisionCellStorage {
	public:
		CollisionCellStorage() noexcept;
		CollisionCellStorage(CollisionCellStorage const&) = delete;
		CollisionCellStorage operator= (CollisionCellStorage const&) = delete;

		bool const push(GasUnit* unit) noexcept;
		void attach(CollisionCellStorage* storage) noexcept { next_ = storage; }
		void reset() noexcept { count_ = 0; }

	private:
		friend class CollisionCellIterator;

		GasUnit* units_[COLLISIONCELL_CAPACITY];
		size_t count_;
		CollisionCellStorage* next_;
	};

	class CollisionCell {
	public:
		CollisionCell(CollisionCellStoragePool& pool) noexcept;
		CollisionCell(CollisionCell const&) = delete;
		CollisionCell operator= (CollisionCell) = delete;

		void reset() noexcept;
		void push(GasUnit* unit);

	private:
		friend class CollisionCellIterator;

		CollisionCellStorage main_storage_;
		CollisionCellStorage* plast_storage_;
		CollisionCellStoragePool& pool_;
	};

	class CollisionCellIterator {
	public:
		CollisionCellIterator(CollisionCell& cell) noexcept;
		CollisionCellIterator(CollisionCellIterator const&) = delete;
		CollisionCellIterator operator= (CollisionCellIterator const&) = delete;

		GasUnit* const getNext() noexcept;
		bool const end() const noexcept;

	private:
		CollisionCellStorage* cur_storage_;
		size_t index_;
	};

	class CollisionManager {
	public:

	private:
		size_t nx_;
		size_t ny_;
		size_t nz_;
		
		float sx_;
		float sy_;
		float sz_;

		CollisionCell* cells_;
		CollisionCellStoragePool pool_;
	};
	
	class GasDistributionManager {};
	class ContainerBuilder {};

	class Container {
	public:
		Container() = delete;
		Container(Container const&) = delete;
		Container operator= (Container const&) = delete;

		Container(float width, float height, float depth, float pressure, 
			float temperature)
		{
			// p = nkT, p = N/V * kT
			// N/V = p/kT
			// N = pV/kT
			
			float v = width * height * depth;
			size_t count = pressure * v / (1.380649 * temperature) * 1e23f;
			std::cout << (float)count << std::endl;
		}

		~Container() noexcept = default;

		CollisionData const update(float const dt) noexcept;

	private:
		// ContainerCollider collider_;
		// CollisionManager manager_;
		GasUnit* units_;
		size_t nunits_;

	};



	bool const ResolveCollision(GasUnit& a, GasUnit& b) noexcept;
	bool const ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept;
}

#endif
