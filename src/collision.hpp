#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

#include "math.hpp"
#include "gasunit.hpp"
#include "containercollider.hpp"

namespace Phys {
	

	// bool ResolveCollision(GasUnit& a, GasUnit& b) noexcept;
	inline bool HasCollision(Math::Vec4d apos, Math::Vec4d bpos, 
		double& d2, Math::Vec4d& dr) noexcept;

	__attribute__((noinline))
	void ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, Math::Vec4d& bpos, 
		Math::Vec4d& bvel, double& d2, Math::Vec4d& dr) noexcept;

	inline bool HasCollision(Math::Vec4d apos, ContainerCollider collider, int& mask)
		noexcept;

	__attribute__((noinline))
	// bool ResolveCollision(GasUnit& a, ContainerCollider const& b) noexcept;
	void ResolveCollision(Math::Vec4d& apos, Math::Vec4d& avel, 
			ContainerCollider b, int& cmask) noexcept;
}

namespace Phys {

	inline bool HasCollision(Math::Vec4d apos, Math::Vec4d bpos, double& d2, 
		Math::Vec4d& dr) noexcept
	{
		using namespace Math;

		dr = apos - bpos;
		d2 = dr.sqlen();

		return (d2 < D2);
	}

	inline bool HasCollision(Math::Vec4d apos, ContainerCollider b, int& mask)
		noexcept
	{
		using namespace Math;

		Vec4d Rvec(R);

		mask = 
			_mm256_movemask_pd(
				_mm256_cmp_pd((apos + Rvec).vector, b.size().vector, _CMP_GT_OQ)) |
			(_mm256_movemask_pd(
				_mm256_cmp_pd((apos - Rvec).vector, (-b.size()).vector, _CMP_LT_OQ))
			 	<< 4);

		return mask;
	}


}

#endif
