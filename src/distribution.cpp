#include "gasunit.hpp"
#include "math.hpp"
#include "maxwell.hpp"

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

namespace Phys {
	void SetupPositionDistribution(GasUnit units[], size_t count,
		double width, double height, double depth)
	{		
		/*
		std::vector<Math::Vec4d> positions;

		for(double x = -width + R; x <= width - R; x += D + Math::EPSd*1)
			for(double y = -height + R; y <= height - R; y += D + Math::EPSd*1)
				for(double z = -depth + R; z <= depth - R; z += D + Math::EPSd*1)
					positions.push_back(Math::Vec4d(x, y, z));

		std::cout << positions.size() << std::endl;

		if(positions.size() < count)
			throw std::runtime_error("impossible to distribute gives count of GasUnits");

		std::random_device r;
		std::mt19937_64 g(r());
		std::shuffle(positions.begin(), positions.end(), g);

		for(size_t i = 0; i < count; ++i)
			units[i].pos() = positions[i];
		*/

		std::random_device random_device;
		std::mt19937_64 random_generator(random_device());

		std::uniform_real_distribution x_distribution(-width + R, width - R);
		std::uniform_real_distribution y_distribution(-height + R, height - R);
		std::uniform_real_distribution z_distribution(-depth + R, depth - R);

		for(size_t i = 0; i < count; ++i) {
			units[i].pos() = Math::Vec4d(
				x_distribution(random_generator),
				y_distribution(random_generator),
				z_distribution(random_generator)
			);
		}
	}

	double SetupVelocityDistribution(GasUnit units[], size_t count,
		double massbyk, double temperature, double step_error)
	{
		std::random_device r;
		std::mt19937 g(r());

		MaxwellDistributionManager dmgr(massbyk, temperature, step_error);

		std::cout << "MPV = " << dmgr.mostProbablePosition() << std::endl;

		size_t total = 0;
		double rest = 0.0;
		double maxv = 0.0;
		while(dmgr.needIntegrationStep()) {
			double fpart = count *  dmgr.integrationStep();

			size_t part = (size_t)fpart;
			rest += fpart - (double)part;

			maxv = dmgr.getIntegrationPosition();

			if(rest >= 1.0) {
				size_t extpart = (size_t)rest;
				rest = rest - (double)extpart;

				part += extpart;
			}

			size_t limit = total + part;
			for(; total < limit; ++total) {
				Math::Vec4d dir(
						(double)g() / (double)std::mt19937::max() - 0.5,
						(double)g() / (double)std::mt19937::max() - 0.5,
						/*(double)g() / (double)std::mt19937::max() - 0.5);*/
					0.0);

				dir.norm();

				units[total].vel() = dir * maxv;
			}
		}

		return maxv;
	}
}
