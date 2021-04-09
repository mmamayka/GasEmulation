#ifndef MATH_PLANE_HPP
#define MATH_PLANE_HPP

#include "math-common.hpp"
#include "math-vector.hpp"

namespace Math {
	namespace AUX {
		template<typename DataType>
		class alignas(sizeof(DataType) * 4) Plane {
		public:
			Plane(Vec4<DataType> point, Vec4<DataType> normal) noexcept;
			Plane(Vec4<DataType> p1, Vec4<DataType> p2, Vec4<DataType> p3) noexcept;
			Plane(DataType A, DataType B, DataType C, DataType D) noexcept;

			Vec4<DataType> normal() const noexcept;
			DataType distanceTo(Vec4<DataType> point) const noexcept;
			DataType distanceTo(Vec4<DataType> point, Vec4<DataType> dir) const noexcept;
			Vec4<DataType> proj(Vec4<DataType> point) const noexcept;
		private:
			union {
				typename VecType<DataType>::type vector;
				DataType data[4];

				struct {
					DataType A;
					DataType B;
					DataType C;
					DataType D;
				};
			};
		};
	}

	using PlaneF = AUX::Plane<float>;
	using PlaneD = AUX::Plane<double>;
}


namespace Math {
	namespace AUX {
		template<typename DataType>
		Plane<DataType>::Plane(Vec4<DataType> point, Vec4<DataType> normal) noexcept {
			this->vector = normal.vector;
			this->D = -Dot(normal, point);
		}

		template<typename DataType>
		Plane<DataType>::Plane(Vec4<DataType> p1, Vec4<DataType> p2, Vec4<DataType> p3) 
			noexcept 
		{
			Vec4<DataType> v1 = p2 - p1;
			Vec4<DataType> v2 = p3 - p1;

			Vec4<DataType> normal = Cross(v1, v2);
			normal.norm();

			this->vector = normal.vector;
			this->D = Dot(normal, p1);
		}

		template<typename DataType>
		Plane<DataType>::Plane(DataType A, DataType B, DataType C, DataType D) noexcept {
			this->vector = _mm256_set_pd(D, C, B, A);
		}

		template<typename DataType>
		Vec4<DataType> Plane<DataType>::normal() const noexcept {
			Vec4<DataType> normal(this->vector);
			normal.w = (DataType)0;
			return normal;
		}

		template<typename DataType>
		DataType Plane<DataType>::distanceTo(Vec4<DataType> point) const noexcept {
			point.w = (DataType)1;
			return Dot(point, Vec4<DataType>(this->vector));
		}

		template<typename DataType>
		DataType Plane<DataType>::distanceTo(Vec4<DataType> point, Vec4<DataType> dir) 
			const noexcept
		{
			point.w = (DataType)1;
			return -Dot(Vec4<DataType>(vector), point) / 
				Dot(Vec4<DataType>(vector), dir);
		}

		template<typename DataType>
		Vec4<DataType> Plane<DataType>::proj(Vec4<DataType> point) const noexcept {
			return point - this->normal() * this->distanceTo(point);
		}
	}

}

#endif
