#ifndef MAXWELL_H
#define MAXWELL_H

namespace Phys {
	class MaxwellDistributionManager final {
	public:
		MaxwellDistributionManager(float massbyk, float temperature, float err) noexcept;

		float const pointProbability(float at) const noexcept;
		float const rangeProbability(float start, float end) const noexcept;

		float const mostProbablePosition() const noexcept;
		float const meanSquarePosition() const noexcept;

		void resetIntegration() noexcept;
		float const integrationStep() noexcept;
		bool const needIntegrationStep() const noexcept;
		float const getIntegrationPosition() const noexcept;

	private:
		void setupRightLimit() noexcept;

		float A_;
		float sqrtA_;

		float step_;
		float rlimit_;
		float err_;

		float pos_;
	};
}


#endif
