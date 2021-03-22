#ifndef GASUNIT_H
#define GASUNIT_H

#include "math.hpp"

namespace Phys {
	constexpr double R = 0.45;
	constexpr double D = R * 2.0;
	constexpr double D2 = D * D;
	constexpr double M = 1.0;

	class GasUnit {
	public:
		GasUnit() :
			pos_(0.0), vel_(0.0) {}

		GasUnit(Math::Vec4d const& init_pos, Math::Vec4d const& init_vel) noexcept :
			pos_(init_pos), vel_(init_vel) {}

		inline Math::Vec4d const pos() const noexcept { return pos_; }
		inline Math::Vec4d& pos() noexcept { return pos_; }

		inline Math::Vec4d const vel() const noexcept { return vel_; }
		inline Math::Vec4d& vel() noexcept { return vel_; }

		void move(double dt) noexcept { pos_ += vel_ * dt; }

	private:
		Math::Vec4d pos_;
		Math::Vec4d vel_;
	};
}

#endif
