#ifndef GASUNIT_H
#define GASUNIT_H

#include "math.hpp"

namespace Phys {
	constexpr float R = 0.75f;
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
		GasUnit() :
			pos_(0.f), vel_(0.f) {}

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

	void SetupPositionDistribution(GasUnit units[], size_t count,
		float width, float height, float depth);

	float const SetupVelocityDistribution(GasUnit units[], size_t count,
		float massbyk, float temperature, float step_error);
}

#endif
