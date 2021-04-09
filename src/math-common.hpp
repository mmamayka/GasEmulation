#ifndef MATH_COMMON_HPP
#define MATH_COMMON_HPP

#include <cmath>
#include <immintrin.h>

namespace Math {
	namespace AUX {
		template<typename DataType> struct VecType;

		template<>
		struct VecType<float> { using type = __m128; };

		template<>
		struct VecType<double> { using type = __m256d; };

		constexpr int FLOATVEC_ABSMASK = ~(1 << 31);
		constexpr long long DOUBLEVEC_ABSMASK = ~(1ll << 63);
	}

	constexpr float EPSf = 1e-5f;
	constexpr double EPSd = 1e-9;

	constexpr float PIf = 3.14159265358979f;
	constexpr double PId = 3.14159265358979;

	inline float Abs(float x) noexcept;
	inline double Abs(double x) noexcept;

	inline bool AboutZero(float x) noexcept;
	inline bool AboutZero(double x) noexcept;

	inline bool Equal(float x, float y) noexcept;
	inline bool Equal(double x, double y) noexcept;

	inline float Sqrt(float x) noexcept;
	inline double Sqrt(double x) noexcept;
}

namespace Math {
	inline float Abs(float x) noexcept {
		__m128 xvec = _mm_load_ss(&x);
		__m128 maskvec = _mm_load_ss(
			reinterpret_cast<float const*>(&AUX::FLOATVEC_ABSMASK));
		__m128 absvec = _mm_and_ps(xvec, maskvec);

		float result = NAN;
		_mm_store_ss(&result, absvec);
		return result;
	}

	inline double Abs(double x) noexcept {
		__m128d xvec = _mm_load_sd(&x);
		__m128d maskvec = _mm_load_sd(
			reinterpret_cast<double const*>(&AUX::DOUBLEVEC_ABSMASK));
		__m128d absvec = _mm_and_pd(xvec, maskvec);

		double result = NAN;
		_mm_store_sd(&result, absvec);
		return result;
	}

	inline bool AboutZero(float x) noexcept { return Abs(x) < EPSf; }
	inline bool AboutZero(double x) noexcept { return Abs(x) < EPSd; }

	inline bool Equal(float x, float y) noexcept { return Abs(x - y) < EPSf; }
	inline bool Equal(double x, double y) noexcept { return Abs(x - y) < EPSd; }

	inline float Sqrt(float x) noexcept {
		__m128 xvec = _mm_load_ss(&x);
		__m128 sqrtvec = _mm_sqrt_ss(xvec);

		float result = NAN;
		_mm_store_ss(&result, sqrtvec);
		return result;
	}

	inline double Sqrt(double x) noexcept {
		__m128d xvec = _mm_load_sd(&x);
		__m128d sqrtvec = _mm_sqrt_sd(xvec, xvec);

		double result = NAN;
		_mm_store_sd(&result, sqrtvec);
		return result;
	}
}



#endif
