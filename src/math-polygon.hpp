#ifndef MATH_POLYGON_HPP
#define MATH_POLYGON_HPP

#include "math-common.hpp"
#include "math-vector.hpp"
#include "math-plane.hpp"
#include "math-aabb.hpp"

#include <initializer_list>
#include <iterator>
#include <algorithm>
#include <utility>
#include <new>

#include <iostream>

namespace Math {
	namespace AUX {
		template<typename DataType>
		class PolygonIterator;

		template<typename DataType>
		class Polygon;

		template<typename DataType>
		PolygonIterator<DataType> operator+(PolygonIterator<DataType> a,
			typename PolygonIterator<DataType>::difference_type d) noexcept;

		template<typename DataType>
		PolygonIterator<DataType> operator-(PolygonIterator<DataType> a,
			typename PolygonIterator<DataType>::difference_type d) noexcept;

		template<typename DataType>
		class PolygonIterator : 
			public std::iterator<std::random_access_iterator_tag, Polygon<DataType>>
		{
		public:
			PolygonIterator operator++() noexcept { return ++position_; }
			PolygonIterator operator++(int) noexcept { return position_++; }

			PolygonIterator operator+= (
				typename PolygonIterator<DataType>::difference_type d
			) noexcept { return position_ += d; }

			PolygonIterator operator-= (
				typename PolygonIterator<DataType>::difference_type d
			) noexcept { return position_ -= d; }

			typename PolygonIterator<DataType>::reference operator*() const
			{ return *position_; }

		private:
			friend class Polygon<DataType>;

			friend PolygonIterator<DataType> operator+<>(PolygonIterator<DataType> a,
				typename PolygonIterator<DataType>::difference_type d) noexcept;

			friend PolygonIterator<DataType> operator-<>(PolygonIterator<DataType> a,
				typename PolygonIterator<DataType>::difference_type d) noexcept;

			PolygonIterator(Vec4<DataType>* position_) noexcept;

			DataType* position_;
		};

		template<typename DataType>
		bool operator== (PolygonIterator<DataType> a, PolygonIterator<DataType> b)
			noexcept { return &*a == &*b; }

		template<typename DataType>
		bool operator!= (PolygonIterator<DataType> a, PolygonIterator<DataType> b)
			noexcept { return &*a != &*b; }

		template<typename DataType>
		bool operator< (PolygonIterator<DataType> a, PolygonIterator<DataType> b)
			noexcept { return &*a < &*b; }

		template<typename DataType>
		bool operator> (PolygonIterator<DataType> a, PolygonIterator<DataType> b)
			noexcept { return &*a > &*b; }

		template<typename DataType>
		bool operator<= (PolygonIterator<DataType> a, PolygonIterator<DataType> b)
			noexcept { return &*a <= &*b; }

		template<typename DataType>
		bool operator>= (PolygonIterator<DataType> a, PolygonIterator<DataType> b)
			noexcept { return &*a >= &*b; }

		template<typename DataType>
		PolygonIterator<DataType> operator+(PolygonIterator<DataType> a,
			typename PolygonIterator<DataType>::difference_type d) noexcept
		{ return a.position_ + d; }

		template<typename DataType>
		PolygonIterator<DataType> operator+(
			typename PolygonIterator<DataType>::difference_type d, 
			PolygonIterator<DataType> a) noexcept
		{ return a + d; }

		template<typename DataType>
		PolygonIterator<DataType> operator-(PolygonIterator<DataType> a,
			typename PolygonIterator<DataType>::difference_type d) noexcept
		{ return a.position_ - d; }

		template<typename DataType>
		class Polygon {
		public:
			using iterator = PolygonIterator<DataType>;
			using const_iterator = PolygonIterator<const DataType>;

			Polygon(size_t npoints, Vec4<DataType>* points) noexcept;
			Polygon(std::initializer_list<Vec4<DataType>> points) noexcept;

			Polygon(const Polygon<DataType>& p);
			Polygon(Polygon<DataType>&& p) noexcept;

			Polygon operator= (Polygon<DataType> const& p);
			Polygon operator= (Polygon<DataType>&& p) noexcept;

			~Polygon();

			// Return NAN is case when projection point is out of polygon
			DataType distanceTo(Vec4<DataType> point) const noexcept;
			DataType distanceTo(Vec4<DataType> point, Vec4<DataType> dir) const noexcept;
			bool contain(Vec4<DataType> point) const noexcept;

			Polygon<DataType> bisection(Plane<DataType> p) const noexcept;
			
			Plane<DataType> getPlane() const noexcept;
			size_t getPointCount() const noexcept;

			Vec4<DataType>& operator[] (size_t index) noexcept 
			{ return points_[index]; }

			Vec4<DataType> const& operator[] (size_t index) const noexcept 
			{ return points_[index]; }

			iterator begin() noexcept { return iterator(points_); }
			iterator end() noexcept { return iterator(points_ + count_); }

			const_iterator cbegin() noexcept { return const_iterator(points_); }
			const_iterator cend() noexcept { return const_iterator(points_ + count_); }

			AABB<DataType> getAABB() const noexcept;

		private:
			void setupCosines() noexcept;

			size_t count_;
			Vec4<DataType>* points_;
			DataType* cos_;

			Plane<DataType> plane_;
		};
	}

	using PolygonF = AUX::Polygon<float>;
	using PolygonD = AUX::Polygon<double>;
}

namespace Math {
	namespace AUX {
		template<typename DataType>
		Polygon<DataType>::Polygon(size_t npoints, Vec4<DataType>* points) noexcept :
			plane_(points[0], points[1], points[2]),
			points_(new Vec4<DataType>[npoints]),
			cos_(new DataType[npoints - 2]),
			count_(npoints)
		{
			std::copy_n(points, npoints, points_);
			setupCosines();
		}

		template<typename DataType>
		Polygon<DataType>::Polygon(std::initializer_list<Vec4<DataType>> points) 
			noexcept :
			plane_(*points.begin(), *(points.begin() + 1), *(points.begin() + 2)),
			points_(new Vec4<DataType>[points.size()]),
			cos_(new DataType[points.size() - 2]),
			count_(points.size())
		{
			std::copy(points.begin(), points.end(), points_);
			setupCosines();
		}

		template<typename DataType>
		Polygon<DataType>::Polygon(const Polygon<DataType>& p) :
			plane_(p.plane_),
			points_(new Vec4<DataType>[p.count_]),
			cos_(new DataType[p.count_ - 2]),
			count_(p.count_)
		{
			std::copy_n(p.points_, p.count_, points_);
			std::copy_n(p.cos_, p.count_ - 2, cos_);
		}

		template<typename DataType>
		Polygon<DataType>::Polygon(Polygon<DataType>&& p) noexcept :
			points_(p.points_),
			count_(p.count_),
			plane_(p.plane_)
		{
			p.points_ = nullptr;
			p.cos_ = nullptr;
		}

		template<typename DataType>
		Polygon<DataType> Polygon<DataType>::operator= (Polygon<DataType> const& p)
		{
			delete[] points_;
			delete[] cos_;

			plane_ = p.plane_;
			count_ = p.count_;

			points_ = new Vec4<DataType>[p.count_];
			cos_ = new DataType[p.count_ - 2];

			std::copy_n(p.points_, p.count_, points_);
			std::copy_n(p.cos_, p.count_ - 2, cos_);
		}

		template<typename DataType>
		Polygon<DataType> Polygon<DataType>::operator= (Polygon<DataType>&& p) noexcept {
			plane_ = p.plane_;
			count_ = p.count_;
			std::swap(points_, p.points_);
			std::swap(cos_, p.cos_);
		}

		template<typename DataType>
		Polygon<DataType>::~Polygon() {
			if(points_ != nullptr)
				delete[] points_;

			if(cos_ != nullptr)
				delete[] cos_;
		}

		template<typename DataType>
		DataType Polygon<DataType>::distanceTo(Vec4<DataType> point) const noexcept {
			DataType distance = plane_.distanceTo(point);
			Vec4<DataType> proj_point = point - plane_.normal() * distance;
			if(!contain(proj_point))
				return NAN;

			return distance;
		}

		template<typename DataType>
		DataType Polygon<DataType>::distanceTo(Vec4<DataType> point, Vec4<DataType> dir) 
			const noexcept
		{
			DataType distance = plane_.distanceTo(point, dir);
			Vec4<DataType> proj_point = point - distance * dir;
			if(!contain(proj_point))
				return NAN;

			return distance;
		}

		template<typename DataType>
		bool Polygon<DataType>::contain(Vec4<DataType> point) const noexcept {
			Vec4<DataType> left_axis = points_[1] - points_[0];
			Vec4<DataType> right_axis = points_[count_ -1] - points_[0];
			Vec4<DataType> normal = plane_.normal();
			Vec4<DataType> vec = point - points_[0];

			if(Dot(Cross(left_axis, vec), normal) < (DataType)0)
				return false;

			if(Dot(Cross(vec, right_axis), normal) < (DataType)0)
				return false;

			DataType c = 1.0 - Dot(vec, left_axis) / Sqrt(vec.sqlen() * left_axis.sqlen());

			DataType* ang = std::lower_bound(cos_, cos_ + count_ - 3, c);
			size_t angind = ang - cos_;

			Vec4<DataType> lp = points_[angind + 1];
			Vec4<DataType> rp = points_[angind + 2];

			Vec4<DataType> border = rp - lp;
			Vec4<DataType> tvec = point - lp;
			if(Dot(Cross(tvec, border), normal) > (DataType)0)
				return false;

			return true;
		}

		template<typename DataType>
		AABB<DataType> Polygon<DataType>::getAABB() const noexcept {
			DataType left = std::numeric_limits<DataType>::max();
			DataType right = std::numeric_limits<DataType>::min();
			DataType lower = std::numeric_limits<DataType>::max();
			DataType upper = std::numeric_limits<DataType>::min();
			DataType back = std::numeric_limits<DataType>::max();
			DataType front = std::numeric_limits<DataType>::min();

			for(auto point : *this) {
				if(point.x < left) left = point.x;
				if(point.x > right) right = point.x;
				if(point.y < lower) lower = point.y;
				if(point.y > upper) upper = point.y;
				if(point.z < back) back = point.z;
				if(point.z > front) front = point.z;
			}

			return AABB<DataType>(left, right, lower, upper, back, front);
		}

		template<typename DataType>
		void Polygon<DataType>::setupCosines() noexcept {
			Vec4<DataType> axis = points_[1] - points_[0];
			DataType axissqlen = axis.sqlen();
			for(size_t i = 2; i < count_; ++i) {
				Vec4<DataType> v = points_[i] - points_[0];
				cos_[i - 2] = 1.0 - Dot(v, axis) / Sqrt(axissqlen * v.sqlen());
			}
		}
	}
}

#endif
