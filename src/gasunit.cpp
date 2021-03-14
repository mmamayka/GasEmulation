#include "gasunit.hpp"
#include "math.hpp"
#include "maxwell.hpp"

#include <vector>
#include <algorithm>
#include <random>

namespace Phys {
	void SetupPositionDistribution(GasUnit units[], size_t count,
		float width, float height, float depth)
	{
		size_t xcount = (size_t)(2 * width / D);
		size_t ycount = (size_t)(2 * height / D);
		size_t zcount = (size_t)(2 * depth / D);

		if(xcount * ycount * zcount < count) {
			throw std::invalid_argument
				("impossible to distribute without intersections");
		}

		std::vector<Math::Vec4> positions;

		for(float x = -width + R; x <= width - R; x += D)
			for(float y = -height + R; y <= height - R; y += D)
				for(float z = -depth + R; z <= depth - R; z += D)
					positions.push_back(Math::Vec4(x, y, z));

		std::random_device r;
		std::mt19937_64 g(r());
		std::shuffle(positions.begin(), positions.end(), g);

		for(size_t i = 0; i < count; ++i)
			units[i].pos() = positions[i];
	}

	float const SetupVelocityDistribution(GasUnit units[], size_t count,
		float massbyk, float temperature, float step_error)
	{
		std::random_device r;
		std::mt19937 g(r());

		MaxwellDistributionManager dmgr(massbyk, temperature, step_error);

		size_t total = 0;
		float rest = 0.f;
		float maxv = 0.f;
		while(dmgr.needIntegrationStep()) {
			float fpart = count *  dmgr.integrationStep();
			size_t part = (size_t)fpart;
			rest += fpart - (float)part;

			maxv = dmgr.getIntegrationPosition();

			if(rest >= 1.f) {
				size_t extpart = (size_t)rest;
				rest = rest - (float)extpart;

				part += extpart;
			}

			size_t limit = total + part;
			for(; total < limit; ++total) {
				Math::Vec4 dir((float)g() - (float)std::mt19937::max() / 2.f);
				dir.z = 0.f;

				dir.norm();

				units[total].vel() = dir * maxv;
			}
		}

		return maxv;
	}
}
