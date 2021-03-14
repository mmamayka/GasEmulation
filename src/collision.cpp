#include "collision.hpp"

namespace Phys {
	bool const ResolveCollision(GasUnit& a, GasUnit& b) noexcept {
		using namespace Math;

		Vec4 dr = a.pos() - b.pos();

		// test for Axis Aligned Bound AABB collision
		/*
		if(!InfNormLessThan(Abs(dr), D)) { [[likely]]
			return false;
		}
		*/

		// test for circle collision
		float d2 = dr.sqlen();
		if(d2 >= D2) { [[likely]]
			return false;
		}

		Vec4 dv = a.vel() - b.vel();

		// At^2 -2Bt + C = 0
		float A = dv.sqlen();
		float Bhalf = Dot(dv, dr);
		float C = d2 - D2;
		float Dby4 = Bhalf * Bhalf - A * C;
		float D = Sqrt(Dby4);

		float dt = NAN;
		if(Bhalf > 0.f) {
			Bhalf = -Bhalf;
		}
		dt = (Bhalf + D) / A;

		a.pos() -= a.vel() * dt;
		b.pos() -= b.vel() * dt;

		Vec4 new_dr = a.pos() - b.pos();
		Vec4 new_dv = new_dr * Dot(dv, new_dr) / new_dr.sqlen();

		a.vel() -= new_dv;
		b.vel() += new_dv;

		a.pos() += a.vel() * dt;
		b.pos() += b.vel() * dt;

		return true;
	}

	bool const ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept {
		using namespace Math;

		Vec4 Rvec(R);

		int cmask = (CMPGTMask(a.pos() + Rvec, b.size()) | 
			(CMPLTMask(a.pos() - Rvec, -b.size()) << 4));

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
