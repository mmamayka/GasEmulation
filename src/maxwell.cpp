#include <cmath>
#include <iomanip>
#include "maxwell.hpp"
#include "math.hpp"

namespace Phys {

	MaxwellDistributionManager::MaxwellDistributionManager(
		float massbyk, float temperature, float err) noexcept :

		A_(NAN), sqrtA_(NAN), err_(err), pos_(0.f), step_(NAN)
	{
		A_ = massbyk / (2 * temperature);
		sqrtA_ = Math::Sqrt(A_);

		setupRightLimit();

		step_ = mostProbablePosition();
	}

	float const MaxwellDistributionManager::pointProbability(float at) const noexcept
	{
		float vsq = at * at;
		return 4 * Math::PI * powf(A_ / (2 * Math::PI), 1.5f) * 
			vsq * expf(-A_ * vsq);
	}

	float const MaxwellDistributionManager::rangeProbability(float start, 
		float end) const noexcept
	{
		return erff(end * sqrtA_) - erff(start * sqrtA_) +
			2 * sqrtA_ / Math::Sqrt(Math::PI) * (expf(-start * start * A_) * start - 
			expf(-end * end * A_) * end);
	}

	float const MaxwellDistributionManager::mostProbablePosition() const noexcept
	{
		return 1.f / sqrtA_;
	}

	float const MaxwellDistributionManager::meanSquarePosition() const noexcept
	{
		return 1.f / sqrtA_ * sqrtf(3.f / 2.f);
	}

	void MaxwellDistributionManager::resetIntegration() noexcept {
		pos_ = 0.f;
		step_ = mostProbablePosition();
	}

	float const MaxwellDistributionManager::integrationStep() noexcept {
		float max_ystep = 1.f / sqrtA_ * err_;

		float lposy = pointProbability(pos_);
		float rposy = pointProbability(pos_ + step_);

		while(Math::Abs(rposy - lposy) < max_ystep && (pos_ + step_) < rlimit_) {
			step_ *= 2.f;
			rposy = pointProbability(pos_ + step_);

		}

		if(pos_ + step_ < rlimit_) {
			float lpos = pos_;
			float rpos = pos_ + step_;

			while(fabsf(lpos - rpos) > Math::EPS) {
				float mpos = (lpos + rpos) / 2.f;

				float mposy = pointProbability(mpos);
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

		float old_pos = pos_;
		pos_ = pos_ + step_;

		return rangeProbability(old_pos, pos_);
	}

	bool const MaxwellDistributionManager::needIntegrationStep() const noexcept 
	{
		return !Math::Equal(pos_, rlimit_);
	}

	float const MaxwellDistributionManager::getIntegrationPosition() const noexcept 
	{
		return pos_;
	}


	void MaxwellDistributionManager::setupRightLimit() noexcept 
	{
		float llimit = rlimit_ = mostProbablePosition();

		while(!Math::Equal(rangeProbability(0.f, rlimit_), 1.f))
			rlimit_ *= 2.f;

		while(!Math::Equal(llimit, rlimit_)) {
			float mlimit = (llimit + rlimit_) / 2.f;

			if(Math::Equal(rangeProbability(0.f, mlimit), 1.f)) {
				rlimit_ = mlimit;
			}
			else {
				llimit = rlimit_;
			}
		}
	}
}
