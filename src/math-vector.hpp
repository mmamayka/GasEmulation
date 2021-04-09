#ifndef MATH_VECTOR_HPP
#define MATH_VECTOR_HPP

#include "math-common.hpp"

#include <cmath>
#include <immintrin.h>

namespace Math {
	namespace AUX {
		template<typename DataType>
		struct alignas(sizeof(DataType) * 4) Vec4 {
			inline Vec4() noexcept;
			inline Vec4(DataType filler) noexcept;
			inline Vec4(DataType x, DataType y, DataType z, DataType w = 0.f) noexcept;
			inline Vec4(typename VecType<DataType>::type v) noexcept : vector(v) {}

			inline Vec4<DataType> operator+= (Vec4<DataType> other) noexcept;
			inline Vec4<DataType> operator-= (Vec4<DataType> other) noexcept;
			inline Vec4<DataType> operator*= (DataType value) noexcept;
			inline Vec4<DataType> operator/= (DataType value) noexcept;

			inline DataType sqlen() const noexcept;
			inline DataType len() const noexcept;
			inline DataType isqlen() const noexcept;

			inline void norm() noexcept;
			// inline Vec4<DataType> normed() const noexcept;

			inline bool isZero() const noexcept;

			union {
				typename VecType<DataType>::type vector;
				DataType data[4];

				struct {
					DataType x;
					DataType y;
					DataType z;
					DataType w;
				};
			};

		};

		template<typename DataType>
		Vec4<DataType> operator+ (Vec4<DataType> x, Vec4<DataType> y) noexcept;

		template<typename DataType>
		Vec4<DataType> operator- (Vec4<DataType> x, Vec4<DataType> y) noexcept;

		template<typename DataType>
		Vec4<DataType> operator* (Vec4<DataType> x, DataType y) noexcept;

		template<typename DataType>
		Vec4<DataType> operator* (DataType x, Vec4<DataType> y) noexcept;

		template<typename DataType>
		Vec4<DataType> operator/ (Vec4<DataType> x, DataType y) noexcept;

		template<typename DataType>
		bool operator== (Vec4<DataType> x, Vec4<DataType> y) noexcept;

		template<typename DataType>
		bool operator!= (Vec4<DataType> x, Vec4<DataType> y) noexcept;

	}

	using Vec4f = AUX::Vec4<float>;
	using Vec4d = AUX::Vec4<double>;

	inline Vec4f Abs(Vec4f x) noexcept;
	inline Vec4d Abs(Vec4d x) noexcept;

	inline bool AboutZero(Vec4f x) noexcept;
	inline bool AboutZero(Vec4d x) noexcept;

	inline bool Equal(Vec4f x, Vec4f y) noexcept;
	inline bool Equal(Vec4d x, Vec4d y) noexcept;

	inline float Dot(Vec4f x, Vec4f y) noexcept;
	inline double Dot(Vec4d x, Vec4d y) noexcept;

	inline Vec4f Cross(Vec4f x, Vec4f y) noexcept;
	inline Vec4d Cross(Vec4d x, Vec4d y) noexcept;

}

namespace Math {
	namespace AUX {
		template<> inline Vec4<float>::Vec4() noexcept :
			vector(_mm_setzero_ps()) {}

		template<> inline Vec4<double>::Vec4() noexcept :
			vector(_mm256_setzero_pd()) {}

		template<> inline Vec4<float>::Vec4(float filler) noexcept {
			__m128 fillervec = _mm_load_ss(&filler);
			this->vector = _mm_shuffle_ps(fillervec, fillervec, 
				(0 << 0) | (0 << 2) | (0 << 4) | (1 << 6));
		}

		template<> inline Vec4<double>::Vec4(double filler) noexcept {
			__m256d fillervec = _mm256_castpd128_pd256(_mm_load_sd(&filler));
			this->vector = _mm256_permute4x64_pd(fillervec,
				(0 << 0) | (0 << 2) | (0 << 4) | (1 << 6));
		}

		template<> inline Vec4<float>::Vec4(float x, float y, float z, float w) noexcept :
			vector(_mm_set_ps(w, z, y, x)) {}

		template<> inline Vec4<double>::Vec4(double x, double y, double z, double w) 
			noexcept : vector(_mm256_set_pd(w, z, y, x)) {}

		template<> inline Vec4<float> Vec4<float>::operator+= (Vec4<float> other) 
			noexcept 
		{
			this->vector = _mm_add_ps(this->vector, other.vector);
			return *this;
		}

		template<> inline Vec4<double> Vec4<double>::operator+= (Vec4<double> other) 
			noexcept 
		{
			this->vector = _mm256_add_pd(this->vector, other.vector);
			return *this;
		}

		template<> inline Vec4<float> Vec4<float>::operator-= (Vec4<float> other) 
			noexcept 
		{
			this->vector = _mm_sub_ps(this->vector, other.vector);
			return *this;
		}

		template<> inline Vec4<double> Vec4<double>::operator-= (Vec4<double> other) 
			noexcept 
		{
			this->vector = _mm256_sub_pd(this->vector, other.vector);
			return *this;
		}

		template<> inline Vec4<float> Vec4<float>::operator*= (float value) noexcept {
			__m128 vvec = _mm_set1_ps(value);
			this->vector = _mm_mul_ps(this->vector, vvec);
			return *this;
		}
		
		template<> inline Vec4<double> Vec4<double>::operator*= (double value) noexcept {
			__m256d vvec = _mm256_broadcast_sd(&value);
			this->vector = _mm256_mul_pd(this->vector, vvec);
			return *this;
		}

		template<> inline Vec4<float> Vec4<float>::operator/= (float value) noexcept {
			__m128 vvec = _mm_set1_ps(value);
			this->vector = _mm_div_ps(this->vector, vvec);
			return *this;
		}
		
		template<> inline Vec4<double> Vec4<double>::operator/= (double value) noexcept {
			__m256d vvec = _mm256_broadcast_sd(&value);
			this->vector = _mm256_div_pd(this->vector, vvec);
			return *this;
		}

		template<> inline float Vec4<float>::sqlen() const noexcept {
			__m128 sqlenvec = _mm_dp_ps(this->vector, this->vector, 0xF1);

			float result = NAN;
			_mm_store_ss(&result, sqlenvec);
			return result;
		}

		// TODO: can be optimized using smth instead of extract
		template<> inline double Vec4<double>::sqlen() const noexcept {
			__m256d sqvec = _mm256_mul_pd(this->vector, this->vector);
			__m256d h1sumvec = _mm256_hadd_pd(sqvec, sqvec);
			__m128d h2sumvec = _mm256_extractf128_pd(h1sumvec, 1);
			__m128d dotvec = _mm_add_sd(_mm256_castpd256_pd128(h1sumvec), h2sumvec);
			
			double result = NAN;
			_mm_store_sd(&result, dotvec);
			return result;
		}

		template<> inline float Vec4<float>::len() const noexcept {
			return Sqrt(this->sqlen());
		}

		template<> inline double Vec4<double>::len() const noexcept {
			return Sqrt(this->sqlen());
		}

		template<> inline void Vec4<float>::norm() noexcept {
			*this /= this->len();
		}
		
		template<> inline void Vec4<double>::norm() noexcept {
			*this /= this->len();
		}

		template<> inline bool Vec4<float>::isZero() const noexcept {
			__m128 maskvec = _mm_set1_ps(*(float*)&FLOATVEC_ABSMASK);
			__m128 absvec = _mm_and_ps(this->vector, maskvec);
			__m128 epsvec = _mm_set1_ps(EPSf);
			__m128 cmpvec = _mm_cmpgt_ps(absvec, epsvec);

			return !_mm_movemask_ps(cmpvec);
		}

		template<> inline bool Vec4<double>::isZero() const noexcept {
			__m256d maskvec = _mm256_set1_pd(*(double*)&DOUBLEVEC_ABSMASK);
			__m256d absvec = _mm256_and_pd(this->vector, maskvec);
			__m256d epsvec = _mm256_set1_pd(EPSf);
			__m256d cmpvec = _mm256_cmp_pd(absvec, epsvec, _CMP_GT_OQ);

			return !_mm256_movemask_pd(cmpvec);
		}
		
		template<typename DataType>
		Vec4<DataType> operator+ (Vec4<DataType> x, Vec4<DataType> y) noexcept {
			return x += y;
		}

		template<typename DataType>
		Vec4<DataType> operator- (Vec4<DataType> x, Vec4<DataType> y) noexcept {
			return x -= y;
		}

		template<typename DataType>
		Vec4<DataType> operator* (Vec4<DataType> x, DataType y) noexcept {
			return x *= y;
		}

		template<typename DataType>
		Vec4<DataType> operator* (DataType x, Vec4<DataType> y) noexcept { 
			return y * x; 
		}

		template<typename DataType>
		Vec4<DataType> operator/ (Vec4<DataType> x, DataType y) noexcept {
			return x /= y;
		}

		template<typename DataType>
		bool operator== (Vec4<DataType> x, Vec4<DataType> y) noexcept {
			return Equal(x, y);
		}

		template<typename DataType>
		bool operator!= (Vec4<DataType> x, Vec4<DataType> y) noexcept {
			return !Equal(x, y);
		}

		template<typename DataType>
		Vec4<DataType> operator- (Vec4<DataType> v) noexcept {
			return Vec4d() - v;
		}


	}

	inline Vec4f Abs(Vec4f x) noexcept {
		__m128 maskvec = _mm_set1_ps(*(float*)&AUX::FLOATVEC_ABSMASK);
		__m128 absvec = _mm_and_ps(x.vector, maskvec);
		return Vec4f(absvec);
	}

	inline Vec4d Abs(Vec4d x) noexcept {
		__m256d maskvec = _mm256_set1_pd(*(double*)&AUX::DOUBLEVEC_ABSMASK);
		__m256d absvec = _mm256_and_pd(x.vector, maskvec);
		return Vec4d(absvec);
	}

	inline bool AboutZero(Vec4f x) noexcept { return x.isZero(); }
	inline bool AboutZero(Vec4d x) noexcept { return x.isZero(); }

	inline bool Equal(Vec4f x, Vec4f y) noexcept { return (x - y).isZero(); }
	inline bool Equal(Vec4d x, Vec4d y) noexcept { return (x - y).isZero(); }

	inline float Dot(Vec4f x, Vec4f y) noexcept {
		__m128 dotvec = _mm_dp_ps(x.vector, y.vector, 0xF1);

		float result = NAN;
		_mm_store_ss(&result, dotvec);
		return result;
	}

	inline double Dot(Vec4d x, Vec4d y) noexcept {
		/*
		__m256d sqvec = _mm256_mul_pd(x.vector, y.vector);
		__m256d h1sumvec = _mm256_hadd_pd(sqvec, sqvec);
		__m128d h2sumvec = _mm256_extractf128_pd(h1sumvec, 1);
		__m128d dotvec = _mm_add_sd(_mm256_castpd256_pd128(h1sumvec), h2sumvec);
		*/

		__m256d xy = _mm256_mul_pd(x.vector, y.vector);
		__m128d xylow = _mm256_castpd256_pd128(xy);
		__m128d xyhigh = _mm256_extractf128_pd(xy, 1);
		__m128d sum1 = _mm_add_pd(xylow, xyhigh);
		__m128d swapped = _mm_unpackhi_pd(sum1, sum1);
		__m128d dotvec = _mm_add_sd(sum1, swapped);
		
		double result = NAN;
		_mm_store_sd(&result, dotvec);
		return result;
	}

	inline Vec4f Cross(Vec4f x, Vec4f y) noexcept {
		__m128 v1reg = _mm_shuffle_ps(x.vector, x.vector, 
			(1 << 0) | (2 << 2) | (0 << 4) | (3 << 6));

		__m128 v2reg = _mm_shuffle_ps(y.vector, y.vector,
			(2 << 0) | (0 << 2) | (1 << 4) | (3 << 6));

		__m128 v3reg = _mm_shuffle_ps(x.vector, x.vector,
			(2 << 0) | (0 << 2) | (1 << 4) | (3 << 6));

		__m128 v4reg = _mm_shuffle_ps(y.vector, y.vector,
			(1 << 0) | (2 << 2) | (0 << 4) | (3 << 6));

		__m128 m2reg = _mm_mul_ps(v3reg, v4reg);
		__m128 resreg = _mm_fmsub_ps(v1reg, v2reg, m2reg);

		return Vec4f(resreg);
	}

	inline Vec4d Cross(Vec4d x, Vec4d y) noexcept {
		__m256d v1reg = _mm256_permute4x64_pd(x.vector,
			(1 << 0) | (2 << 2) | (0 << 4) | (3 << 6));

		__m256d v2reg = _mm256_permute4x64_pd(y.vector,
			(2 << 0) | (0 << 2) | (1 << 4) | (3 << 6));

		__m256d v3reg = _mm256_permute4x64_pd(x.vector,
			(2 << 0) | (0 << 2) | (1 << 4) | (3 << 6));

		__m256d v4reg = _mm256_permute4x64_pd(y.vector,
			(1 << 0) | (2 << 2) | (0 << 4) | (3 << 6));

		__m256d m2reg = _mm256_mul_pd(v3reg, v4reg);
		__m256d resreg = _mm256_fmsub_pd(v1reg, v2reg, m2reg);

		return Vec4d(resreg);
	}
}


#endif
