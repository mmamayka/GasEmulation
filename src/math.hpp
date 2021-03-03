#ifndef MATH_HPP
#define MATH_HPP

#include <ostream>
#include <cassert>
#include <cstdint>
#include <immintrin.h>
#include <cmath>
#include "debug.hpp"

#ifdef NDEBUG

#define NATH_VEC4_DUMP(v)
#define MATH_VEC4_ASSERT(v)

#else

#define MATH_VEC4_DUMP(dump_stream, v) \
	(v).dump_(dump_stream, __FILE__, __PRETTY_FUNCTION__, __LINE__)

#define MATH_VEC4_ASSERT(v) \
		(v).assert_(__FILE__, __PRETTY_FUNCTION__, __LINE__)

#endif

namespace Math {
	namespace AUX {
		inline __m128 const SSE_Abs(__m128 vec) {
			__m128i maskreg = _mm_set1_epi32(~(1 << 31));
			return _mm_and_ps(vec, *(__m128*)&maskreg);
		}

		template<int x, int y, int z, int w>
		struct SSE_ShufMaskS {
			static_assert(x >= 0 && x <= 2, "invalid x index");
			static_assert(y >= 0 && y <= 2, "invalid y index");
			static_assert(z >= 0 && z <= 2, "invalid z index");
			static_assert(w >= 0 && w <= 2, "invalid w index");

			static constexpr int Value = (x << 0) | (y << 2) | (z << 4) | (w << 6);
		};

		template<int x, int y, int z, int w>
		constexpr int SSE_ShufMask = SSE_ShufMaskS<x, y, z, w>::Value;
	}

	constexpr float EPS = 1e-6;

	// TODO: check fabsf realization, fix it
	inline bool const AboutZero(float a) noexcept {
		return fabsf(a) < EPS;
	}
	inline bool const Equal(float x, float y) noexcept {
		return fabsf(x - y) < EPS;
	}

	// Fucked sqrtf call forces compiler push all xmm registers into stack
	// This function - no
	inline float const Sqrt(float x) {
		float res = NAN;
		_mm_store_ps(&res, _mm_sqrt_ss(_mm_load_ss(&x)));
		return res;
	}

	struct Vec4 final {
		Vec4() = delete;

		inline Vec4(float filler) noexcept;
		inline Vec4(float x, float y, float z, float w = 0.f) noexcept;
		inline Vec4(const Vec4& v) noexcept;

		inline Vec4 const& operator= (Vec4 const& v) noexcept;

		inline Vec4 const& operator+= (Vec4 const& v) noexcept;
		inline Vec4 const& operator-= (Vec4 const& v) noexcept;
		inline Vec4 const& operator*= (float v) noexcept;
		inline Vec4 const& operator/= (float v) noexcept;

		inline bool const isZero() const noexcept;

		inline operator bool() const noexcept { return !isZero(); }
		inline bool const operator! () const noexcept { return isZero(); }

		inline float const sqlen() const noexcept;
		inline float const len() const noexcept;
		inline float const ilen() const noexcept;
		inline float const isqlen() const noexcept;

		inline void norm() noexcept;

		// TODO:
		// Vec4 const normed() const noexcept;

		// TODO:
		inline void refl(Vec4 const& normal) noexcept;
		inline void reflu(Vec4 const& normal) noexcept;
		// Vec4 const refled(Vec4 const& normal) const noexcept;

		bool const ok() const noexcept;
		void dump_(std::ostream& dump_stream, char const* file, char const* func, 
			size_t line) const;
		void assert_(char const* file, char const* func, size_t line) const;

		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};

			float data[4];
		};

	protected:
		friend inline Vec4 const operator+ (Vec4 const& x, Vec4 const& y) noexcept;
		friend inline Vec4 const operator- (Vec4 const& x, Vec4 const& y) noexcept;
		friend inline Vec4 const operator* (Vec4 const& x, float y) noexcept;
		friend inline Vec4 const operator/ (Vec4 const& x, float y) noexcept;
		friend inline Vec4 const operator- (Vec4 const& x) noexcept;

		friend inline Vec4 const Abs(Vec4 const& a) noexcept;

		friend Vec4 const Cross(Vec4 const& a, Vec4 const& b) noexcept;

		// TODO: Fix it
		inline Vec4(__m128 data_reg) noexcept { _mm_store_ps(data, data_reg); }
	};

	inline bool const operator== (Vec4 const& x, Vec4 const& y) noexcept;
	inline bool const operator!= (Vec4 const& x, Vec4 const& y) noexcept;

	inline Vec4 const operator+ (Vec4 const& x, Vec4 const& y) noexcept;
	inline Vec4 const operator- (Vec4 const& x, Vec4 const& y) noexcept;

	inline Vec4 const operator* (Vec4 const& x, float y) noexcept;
	inline Vec4 const operator* (float x, Vec4 const& y) noexcept { return y * x; }
	inline Vec4 const operator/ (Vec4 const& x, float y) noexcept;

	inline Vec4 const operator- (Vec4 const& x) noexcept {
		__m128 xreg = _mm_load_ps(x.data);
		__m128 zreg = _mm_setzero_ps();
		__m128 rreg = _mm_sub_ps(zreg, xreg);
		return Vec4(rreg);
	}

	inline float const Dot(Vec4 const& a, Vec4 const& b) noexcept;
	inline Vec4 const Cross(Vec4 const& a, Vec4 const& b) noexcept;

	inline Vec4 const Abs(Vec4 const& a) noexcept {
		return Vec4(AUX::SSE_Abs(_mm_load_ps(a.data)));
	}

	inline int const CMPLTMask(Vec4 const& a, Vec4 const& b) noexcept {
		__m128 areg = _mm_load_ps(a.data);
		__m128 breg = _mm_load_ps(b.data);
		__m128 cmpreg = _mm_cmplt_ps(areg, breg);
		return _mm_movemask_ps(cmpreg);
	}

	inline int const CMPGTMask(Vec4 const& a, Vec4 const& b) noexcept {
		__m128 areg = _mm_load_ps(a.data);
		__m128 breg = _mm_load_ps(b.data);
		__m128 cmpreg = _mm_cmpgt_ps(areg, breg);
		return _mm_movemask_ps(cmpreg);
	}

	inline bool const InfNormLessThan(Vec4 const& a, float b) noexcept {
		// TODO: Try to use cmov
		__m128 areg = _mm_load_ps(a.data);
		__m128 absreg = AUX::SSE_Abs(areg);

		__m128 breg = _mm_set1_ps(b);
		__m128 cmpreg = _mm_cmpge_ps(absreg, breg);

		return !_mm_movemask_ps(cmpreg);
	}

	struct Mat4 final {
		Mat4() noexcept;
		Mat4(float x11, float x12, float x13, float x14,
			 float x21, float x22, float x23, float x24,
			 float x31, float x32, float x33, float x34,
			 float x41, float x42, float x43, float x44) noexcept;

		Mat4(float data[16]) noexcept;

		float const det() const noexcept;

		void inv() noexcept;

		Mat4 const operator+= (Mat4 const& m);
		Mat4 const operator*= (Mat4 const& m);
		Mat4 const operator*= (float m);
		Mat4 const operator/= (float m);
		
		union {
			struct {
				float x11, x12, x13, x14;
				float x21, x22, x23, x24;
				float x31, x32, x33, x34;
				float x41, x42, x43, x44;
			};
			struct {
				float row1[4];
				float row2[4];
				float row3[4];
				float row4[4];
			};
			float data[16];
		};
	};

	std::ostream& operator<< (std::ostream& stream, Vec4 const& v);
}

#include "math.inl"

#endif
