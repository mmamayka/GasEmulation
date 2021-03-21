#ifndef MAXWELL_H
#define MAXWELL_H

namespace Phys {
	class MaxwellDistributionManager final {
	public:
		MaxwellDistributionManager(double massbyk, double temperature, double err) 
			noexcept;

		double pointProbability(double at) const noexcept;
		double rangeProbability(double start, double end) const noexcept;

		double mostProbablePosition() const noexcept;
		double meanSquarePosition() const noexcept;

		void resetIntegration() noexcept;
		double integrationStep() noexcept;
		bool needIntegrationStep() const noexcept;
		double getIntegrationPosition() const noexcept;

	private:
		void setupRightLimit() noexcept;

		double A_;
		double sqrtA_;

		double step_;
		double rlimit_;
		double err_;

		double pos_;
	};
}


#endif
