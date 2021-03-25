#include "collision.hpp"

namespace Phys {
	void ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, Math::Vec4d& bpos, 
		Math::Vec4d& bvel, double& d2, Math::Vec4d& dr) noexcept
	{
		using namespace Math;

		Vec4d dv = avel - bvel;


		// At^2 -2Bt + C = 0
		double A = dv.sqlen();

		if(AboutZero(A)) { [[unlikely]]
			return;
		}
		else {
			double Bhalf = Dot(dv, dr);
			double C = d2 - D2;
			double dt = NAN;
			double Dby4 = Bhalf * Bhalf - A * C;
			double D = Sqrt(Dby4);

			if(Bhalf > 0.0) {
				Bhalf = -Bhalf;
			}
			dt = (Bhalf + D) / A;

			apos -= avel * dt;
			bpos -= bvel * dt;

			Vec4d new_dr = apos - bpos;
			Vec4d new_dv = new_dr * Dot(dv, new_dr) / new_dr.sqlen();

			avel -= new_dv;
			bvel += new_dv;

			apos += avel * dt;
			bpos += bvel * dt;

		}
	}


	void ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, 
			ContainerCollider b, int& cmask) noexcept 
	{
		// rewrite using SSE and masking
		if(cmask & (1 << 0)) {
			avel.x = -avel.x;
			apos.x -= 2 * (apos.x + R - b.size().x);
		}
		if(cmask & (1 << 1)) {
			avel.y = -avel.y;
			apos.y -= 2 * (apos.y + R - b.size().y);
		}
		if(cmask & (1 << 2)) {
			avel.z = -avel.z;
			apos.z -= 2 * (apos.z + R - b.size().z);
		}

		if(cmask & (1 << 4)) {
			avel.x = -avel.x;
			apos.x += 2 * (-apos.x - b.size().x + R);
		}
		if(cmask & (1 << 5)) {
			avel.y = -avel.y;
			apos.y += 2 * (-apos.y - b.size().y + R);
		}
		if(cmask & (1 << 6)) {
			avel.z = -avel.z;
			apos.z += 2 * (-apos.z - b.size().z + R);
		}
	}

}
