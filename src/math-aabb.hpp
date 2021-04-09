#ifndef MATH_AABB_H
#define MATH_AABB_H

#include "math-vector.hpp"

namespace Math {
	namespace AUX {
		template<typename DataType>
		struct AABB {
			AABB(DataType left, DataType right, DataType lower, DataType upper,
				DataType front, DataType back) noexcept :

				left(left),
				right(right),
				lower(lower),
				upper(upper),
				front(front),
				back(back)
			{}

			bool contain(Vec4<DataType> point) const noexcept;
			Vec4<DataType> getOrigin() const noexcept;
			Vec4<DataType> getSize() const noexcept;

			DataType left;
			DataType right;
			DataType lower;
			DataType upper;
			DataType front;
			DataType back;
		};

		template<typename DataType>
		AABB<DataType> Unite(AABB<DataType> const& a, AABB<DataType> const& b) noexcept {
			return AABB(
				a.left < b.left ? a.left : b.left,
				a.right > b.right ? a.right : b.right,
				a.lower < b.lower ? a.lower : b.lower,
				a.upper > b.upper ? a.upper : b.upper,
				a.back < b.back ? a.back : b.back,
				a.front > b.front ? a.front : b.front
			);
		}

		template<typename DataType>
		Vec4<DataType> AABB<DataType>::getOrigin() const noexcept {
			return Vec4<DataType>(left, lower, back);
		}

		template<typename DataType>
		Vec4<DataType> AABB<DataType>::getSize() const noexcept {
			return Vec4<DataType>(right - left, upper - lower, front - back);
		}
	}

	using AABBF = AUX::AABB<float>;
	using AABBD = AUX::AABB<double>;

	inline AABBF Unite(AABBF const& a, AABBF const& b) noexcept 
	{ return AUX::Unite(a, b); }

	inline AABBD Unite(AABBD const& a, AABBD const& b) noexcept 
	{ return AUX::Unite(a, b); }
}

#endif
