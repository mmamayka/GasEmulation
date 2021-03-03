#include "math.hpp"
#include "gasunit.hpp"
#include "tests.hpp"

namespace Phys {

	// TODO: Fix physics, fix math
	bool const ResolveCollision(GasUnit& a, GasUnit& b) noexcept {
		using namespace Math;

		Vec4 dr = a.pos() - b.pos();

		// test for Axis Aligned Bound AABB collision
		if(!InfNormLessThan(Abs(dr), D)) { [[likely]]
			return false;
		}

		// test for circle collision
		float d2 = dr.sqlen();
		if(d2 >= D2) { [[likely]]
			return false;
		}

		// collision resolution
		
		Vec4 dv = a.vel() - b.vel();
		
		float A = dv.sqlen();
		float B = Dot(dr,dv) + Dot(a.pos(), a.vel()) +
			Dot(b.pos(), b.vel());
		float C = dr.sqlen() - D2;

		float dt = (B + Sqrt(B * B - 4 * A * C)) / (2 * A);

		a.pos() -= a.vel() * dt;
		b.pos() -= b.vel() * dt;

		// can be optimized, because dr squared len is known
		a.vel().reflu(dr);
		b.vel().reflu(dr);

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
