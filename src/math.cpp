#include "debug.hpp"
#include "math.hpp"
#include "tests.hpp"

using namespace Math;

UNIT_TEST("Sqrt", "Math") {
	UNIT_ASSERT(Equal(Sqrt(25.0), 5.0));
}

UNIT_TEST("Vec4d", "Math::Vec4d") {
	Vec4d defvec;
	Vec4d xyzwvec(1.0, 2.0, 3.0, 4.0);
	Vec4d filledvec(1.0);

	UNIT_ASSERT(defvec.x == 0.0 && defvec.y == 0.0 && 
		defvec.z == 0.0 && defvec.w == 0.0);

	UNIT_ASSERT(xyzwvec.x = 1.0 && xyzwvec.y == 2.0 &&
			xyzwvec.z == 3.0 && xyzwvec.w == 4.0);

	UNIT_ASSERT(filledvec.x == 1.0 && filledvec.y == 1.0 && 
		filledvec.z == 1.0 && filledvec.w == 0.0);
}

UNIT_TEST("operator+=", "Math::Vec4d") {
	Vec4d vec1(1.0, 2.0, 3.0, 4.0);
	Vec4d vec2(5.0, 6.0, 7.0, 8.0);

	vec2 += vec1;
	UNIT_ASSERT(vec2 == Vec4d(6.0, 8.0, 10.0, 12.0));
}

UNIT_TEST("operator-=", "Math::Vec4d") {
	Vec4d vec1(1.0, 2.0, 3.0, 4.0);
	Vec4d vec2(5.0, 6.0, 7.0, 8.0);

	vec2 -= vec1;
	UNIT_ASSERT(vec2 == Vec4d(4.0, 4.0, 4.0, 4.0));
}

UNIT_TEST("operator*=", "Math::Vec4d") {
	Vec4d vec(1.0, 2.0, 3.0, 4.0);

	vec *= 2.0;
	UNIT_ASSERT(vec == Vec4d(2.0, 4.0, 6.0, 8.0));
}

UNIT_TEST("operator/=", "Math::Vec4d") {
	Vec4d vec(1.0, 2.0, 3.0, 4.0);

	vec /= 2.0;
	UNIT_ASSERT(vec == Vec4d(0.5, 1.0, 1.5, 2.0));
}

UNIT_TEST("sqlen()", "Math::Vec4d") {
	Vec4d vec(1.0, 2.0, 3.0, 4.0);
	UNIT_ASSERT(vec.sqlen() == 1.0 + 4.0 + 9.0 + 16.0);
}
UNIT_TEST("len()", "Math::Vec4d") {
	Vec4d vec(1.0, 2.0, 3.0, 4.0);
	UNIT_ASSERT(Equal(vec.len(), sqrt(1.0 + 4.0 + 9.0 + 16.0)));
}

UNIT_TEST("Dot", "Math") {
	Vec4d vec1(1.0, 2.0, 3.0, 4.0);
	Vec4d vec2(5.0, 6.0, 7.0, 8.0);

	UNIT_ASSERT(Equal(Dot(vec1, vec2), 5.0 + 12.0 + 21.0 + 32.0));
}

UNIT_TEST("operator==", "Math") {
	UNIT_ASSERT(Vec4d(1.0, 2.0, 3.0, 4.0) == Vec4d(1.0, 2.0, 3.0, 4.0));
	UNIT_ASSERT(Vec4d(1.0 + EPSd / 2.0, 2.0, 3.0, 4.0) == Vec4d(1.0, 2.0, 3.0, 4.0));
	UNIT_ASSERT(Vec4d(1.0, 2.0 + EPSd / 2.0, 3.0, 4.0) == Vec4d(1.0, 2.0, 3.0, 4.0));
	UNIT_ASSERT(Vec4d(1.0, 2.0, 3.0 + EPSd / 2.0, 4.0) == Vec4d(1.0, 2.0, 3.0, 4.0));
	UNIT_ASSERT(Vec4d(1.0, 2.0, 3.0, 4.0 + EPSd / 2.0) == Vec4d(1.0, 2.0, 3.0, 4.0));
}

UNIT_TEST("operator-", "Math") {
	Vec4d vec1(1.0, 2.0, 3.0, 4.0);
	Vec4d vec2(5.0, 6.0, 7.0, 8.0);

	Vec4d dif = vec2 - vec1;

	UNIT_ASSERT(dif == Vec4d(4.0, 4.0, 4.0, 4.0));
}
