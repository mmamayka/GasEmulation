#include <cmath>
#include <iomanip>
#include "maxwell.hpp"
#include "math.hpp"
#include <iostream>

namespace Phys {

	MaxwellDistributionManager::MaxwellDistributionManager(
		double massbyk, double temperature, double err) noexcept :

		A_(NAN), sqrtA_(NAN), step_(NAN), err_(err), pos_(0.0)
	{
		A_ = massbyk / (2 * temperature);
		sqrtA_ = Math::Sqrt(A_);

		setupRightLimit();

		step_ = mostProbablePosition();
	}

	double MaxwellDistributionManager::pointProbability(double at) const noexcept
	{
		double vsq = at * at;
		return 4 * Math::PId * pow(A_ / (2 * Math::PId), 1.5f) * 
			vsq * exp(-A_ * vsq);
	}

	double MaxwellDistributionManager::rangeProbability(double start, 
		double end) const noexcept
	{
		return erf(end * sqrtA_) - erf(start * sqrtA_) +
			2 * sqrtA_ / Math::Sqrt(Math::PId) * (exp(-start * start * A_) * start - 
			exp(-end * end * A_) * end);
	}

	double MaxwellDistributionManager::mostProbablePosition() const noexcept
	{
		return 1.0 / sqrtA_;
	}

	double MaxwellDistributionManager::meanSquarePosition() const noexcept
	{
		return 1.0 / sqrtA_ * sqrtf(3.0 / 2.0);
	}

	void MaxwellDistributionManager::resetIntegration() noexcept {
		pos_ = 0.0;
		step_ = mostProbablePosition();
	}

	double MaxwellDistributionManager::integrationStep() noexcept {
		double max_ystep = 1.0 / sqrtA_ * err_;

		double lposy = pointProbability(pos_);
		double rposy = pointProbability(pos_ + step_);

		while(Math::Abs(rposy - lposy) < max_ystep && (pos_ + step_) < rlimit_) {
			step_ *= 2.0;
			rposy = pointProbability(pos_ + step_);

		}

		if(pos_ + step_ < rlimit_) {
			double lpos = pos_;
			double rpos = pos_ + step_;

			while(fabs(lpos - rpos) > Math::EPSd) {
				double mpos = (lpos + rpos) / 2.0;

				double mposy = pointProbability(mpos);
				if(Math::Abs(mposy - lposy) < max_ystep) {
					lpos = mpos;
					lposy = mposy;
				}
				else {
					rpos = mpos;
					rposy = mposy;
				}
			}

			step_ = rpos - pos_;
		}
		else {
			step_ = rlimit_ - pos_;
		}

		double old_pos = pos_;
		pos_ = pos_ + step_;

		return rangeProbability(old_pos, pos_);
	}

	bool MaxwellDistributionManager::needIntegrationStep() const noexcept 
	{
		return !Math::Equal(pos_, rlimit_);
	}

	double MaxwellDistributionManager::getIntegrationPosition() const noexcept 
	{
		return pos_;
	}


	void MaxwellDistributionManager::setupRightLimit() noexcept 
	{
		double llimit = rlimit_ = mostProbablePosition();

		while(!Math::Equal(rangeProbability(0.0, rlimit_), 1.0))
			rlimit_ *= 2.0;

		while(!Math::Equal(llimit, rlimit_)) {
			double mlimit = (llimit + rlimit_) / 2.0;

			if(Math::Equal(rangeProbability(0.0, mlimit), 1.0)) {
				rlimit_ = mlimit;
			}
			else {
				llimit = rlimit_;
			}
		}
	}
}
