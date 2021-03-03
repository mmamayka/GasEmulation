#ifndef GASUNIT_H
#define GASUNIT_H

#include "math.hpp"

namespace Phys {
	constexpr float R = 50.f;
	constexpr float D = R * 2.f;
	constexpr float D2 = D * D;
	constexpr float M = 1.f;

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

	class StatisticData {};
	class CollisionManager {};
	class Container {};

	bool const ResolveCollision(GasUnit& a, GasUnit& b) noexcept;
	bool const ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept;
}

#endif
