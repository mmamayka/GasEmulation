#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

#include "gasunit.hpp"

namespace Phys {
	void SetupPositionDistribution(GasUnit units[], size_t count,
		double width, double height, double depth);

	double SetupVelocityDistribution(GasUnit units[], size_t count,
		double massbyk, double temperature, double step_error);
}

#endif
