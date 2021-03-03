#include "debug.hpp"
#include "math.hpp"
#include "tests.hpp"

namespace Math {
	bool const Vec4::ok() const noexcept {
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && 
			std::isfinite(w);
	}
	void Vec4::dump_(std::ostream& dump_stream, char const* file, char const* func, 
		size_t line) const
	{
		bool okres = ok();
		dump_stream << "class Math::Vec4 [" << this << "] dump from \"" << func << 
			"\" (" << file << ":" << line << "), reason: " << std::boolalpha << okres <<
			" (" << (okres ? "ok" : "has inf or nan term") << ") {" << std::endl;

		dump_stream << "\tx = " << x << std::endl;
		dump_stream << "\ty = " << y << std::endl;
		dump_stream << "\tz = " << z << std::endl;
		dump_stream << "\tw = " << w << std::endl;

		dump_stream << "}" << std::endl;
	}
	void Vec4::assert_(char const* file, char const* func, size_t line) const {
		if(!ok()) {
			dump_(std::cerr, file, func, line);
			ASSERT_(!"invalid Math::Vec4 state", func, file, line);
		}
	}

	Mat4::Mat4() noexcept {
		__m128 r1reg = _mm_setr_ps(1.f, 0.f, 0.f, 0.f);

		_mm_store_ps(row1, r1reg);
		_mm_store_ps(row2, _mm_shuffle_ps(r1reg, r1reg, AUX::SSE_ShufMask<1, 0, 1, 1>));
		_mm_store_ps(row3, _mm_shuffle_ps(r1reg, r1reg, AUX::SSE_ShufMask<1, 1, 0, 1>));
		_mm_store_ps(row4, _mm_shuffle_ps(r1reg, r1reg, AUX::SSE_ShufMask<1, 1, 1, 0>));
	}
}

UNIT_TEST("AboutZero", "Math") {
	UNIT_ASSERT(Math::AboutZero(Math::EPS / 2.f));
	UNIT_ASSERT(Math::AboutZero(-Math::EPS / 2.f));

	UNIT_NASSERT(Math::AboutZero(Math::EPS * 2.f));
	UNIT_NASSERT(Math::AboutZero(-Math::EPS * 2.f));
}

UNIT_TEST("Equal", "Math") {
	UNIT_ASSERT(Math::Equal(5.f, 5.f + Math::EPS / 2));
	UNIT_NASSERT(Math::Equal(5.f, 5.f + Math::EPS * 2));

	UNIT_ASSERT(Math::Equal(-5.f, -5.f + Math::EPS / 2));
	UNIT_NASSERT(Math::Equal(-5.f, -5.f + Math::EPS * 2));

	UNIT_ASSERT(Math::Equal(-Math::EPS / 4, Math::EPS / 4));
	UNIT_NASSERT(Math::Equal(-Math::EPS * 2, Math::EPS * 2));
}

UNIT_TEST("INIT", "Vec4") {
	Math::Vec4 a(1.f, 2.f, 3.f, 4.f);
	Math::Vec4 b(5.f);

	Math::Vec4 c(b);

	UNIT_ASSERT(a.x == 1.f && a.y == 2.f && a.z == 3.f && a.w == 4.f);
	UNIT_ASSERT(b.x == 5.f && b.y == 5.f && b.z == 5.f && b.w == 0.f);
	UNIT_ASSERT(c.x == 5.f && c.y == 5.f && c.z == 5.f && c.w == 0.f);
}

UNIT_TEST("CMP", "Vec4") {
	UNIT_ASSERT(Math::Vec4(1.f, 2.f, 3.f, 4.f) == Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) == Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) == Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) == Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) == Math::Vec4(1.f, 2.f, 3.f, 4.f));

	UNIT_ASSERT(Math::Vec4(1.f + Math::EPS / 2.f, 2.f, 3.f, 4.f) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(1.f, 2.f + Math::EPS / 2.f, 3.f, 4.f) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(1.f, 2.f, 3.f + Math::EPS / 2.f, 4.f) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(1.f, 2.f, 3.f, 4.f + Math::EPS / 2.f) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));

	UNIT_NASSERT(Math::Vec4(1.f + Math::EPS * 2, 2.f, 3.f, 4.f) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(1.f, 2.f + Math::EPS * 2, 3.f, 4.f) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(1.f, 2.f, 3.f + Math::EPS * 2, 4.f) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(1.f, 2.f, 3.f, 4.f + Math::EPS * 2) == 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
}
UNIT_TEST("NCMP", "Vec4") {
	UNIT_NASSERT(Math::Vec4(1.f, 2.f, 3.f, 4.f) != Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) != Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) != Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) != Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(2.f, 2.f, 3.f, 4.f) != Math::Vec4(1.f, 2.f, 3.f, 4.f));

	UNIT_NASSERT(Math::Vec4(1.f + Math::EPS / 2.f, 2.f, 3.f, 4.f) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(1.f, 2.f + Math::EPS / 2.f, 3.f, 4.f) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(1.f, 2.f, 3.f + Math::EPS / 2.f, 4.f) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_NASSERT(Math::Vec4(1.f, 2.f, 3.f, 4.f + Math::EPS / 2.f) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));

	UNIT_ASSERT(Math::Vec4(1.f + Math::EPS * 2, 2.f, 3.f, 4.f) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(1.f, 2.f + Math::EPS * 2, 3.f, 4.f) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(1.f, 2.f, 3.f + Math::EPS * 2, 4.f) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
	UNIT_ASSERT(Math::Vec4(1.f, 2.f, 3.f, 4.f + Math::EPS * 2) != 
		Math::Vec4(1.f, 2.f, 3.f, 4.f));
}

UNIT_TEST("ADD/SUB", "Vec4") {
	Math::Vec4 a(1.f, 2.f, 3.f, 0.f);
	Math::Vec4 b(4.f, 5.f, 6.f, 0.f);

	Math::Vec4 c = a + b;
	Math::Vec4 d = a - b;

	Math::Vec4 f = a;
	Math::Vec4 g = a;

	f += b;
	g -= b;

	Math::Vec4 add_res(5.f, 7.f, 9.f, 0.f);
	Math::Vec4 sub_res(-3.f);

	UNIT_ASSERT(c == add_res);
	UNIT_ASSERT(f == add_res);

	UNIT_ASSERT(d == sub_res);
	UNIT_ASSERT(g == sub_res);
}

UNIT_TEST("MUL/DIV", "Vec4") {
	Math::Vec4 a(2.f, 4.f, 6.f, 8.f);
	Math::Vec4 b(2.f, 4.f, 6.f, 8.f);

	Math::Vec4 c = a * 2.f;
	Math::Vec4 d = a / 2.f;
	Math::Vec4 f = 2.f * a;

	a *= 2.f;
	b /= 2.f;

	Math::Vec4 mul_res(4.f, 8.f, 12.f, 16.f);
	Math::Vec4 div_res(1.f, 2.f, 3.f, 4.f);

	UNIT_ASSERT(c == mul_res);
	UNIT_ASSERT(d == div_res);
	UNIT_ASSERT(f == mul_res);
	UNIT_ASSERT(a == mul_res);
	UNIT_ASSERT(b == div_res);
}

UNIT_TEST("LEN", "Vec4") {
	Math::Vec4 a(1.f, 2.f, 3.f, 4.f);
	float sqlen = 1.f + 4.f + 9.f + 16.f;
	float isqlen = 1.f / sqlen;
	float len = sqrtf(sqlen);
	float ilen = 1.f / len;

	UNIT_ASSERT(Math::Equal(sqlen, a.sqlen()));
	UNIT_ASSERT(Math::Equal(isqlen, a.isqlen()));
	UNIT_ASSERT(Math::Equal(len, a.len()));
	UNIT_ASSERT(Math::Equal(ilen, a.ilen()));
}

UNIT_TEST("NORM", "Vec4") {
	Math::Vec4 a(1.f, 2.f, 3.f, 4.f);
	float len = sqrtf(1.f + 4.f + 9.f + 16.f);

	Math::Vec4 test = a / len;

	a.norm();

	UNIT_ASSERT(test == a);
}

UNIT_TEST("IS-ZERO", "Vec4") {
	UNIT_ASSERT(Math::Vec4(Math::EPS / 2).isZero());
	UNIT_NASSERT(Math::Vec4(Math::EPS * 2).isZero());

}

UNIT_TEST("Dot", "Math") {
	Math::Vec4 a(1.f, 2.f, 3.f, 4.f);
	Math::Vec4 b(5.f, 6.f, 7.f, 8.f);

	float res = 5.f + 12.f + 21.f + 32.f;

	UNIT_ASSERT(Math::Equal(res, Dot(a, b)));
}

UNIT_TEST("Cross", "Math") {
	UNIT_ASSERT(Math::Cross(Math::Vec4(1.f, 2.f, 3.f), Math::Vec4(4.f, 5.f, 6.f)) ==
		Math::Vec4(-3.f, 6.f, -3.f));
}

UNIT_TEST("InfNormLessThan", "Math") {
	using namespace Math;

	UNIT_ASSERT(InfNormLessThan(Vec4(1.f, 2.f, 3.f, 4.f), 5.f));
	UNIT_ASSERT(InfNormLessThan(Vec4(-1.f, 2.f, 3.f, 4.f), 5.f));
	UNIT_ASSERT(InfNormLessThan(Vec4(1.f, -2.f, 3.f, 4.f), 5.f));
	UNIT_ASSERT(InfNormLessThan(Vec4(1.f, 2.f, -3.f, 4.f), 5.f));
	UNIT_ASSERT(InfNormLessThan(Vec4(1.f, 2.f, 3.f, -4.f), 5.f));

	UNIT_NASSERT(InfNormLessThan(Vec4(6.f, 2.f, 3.f, 4.f), 5.f));
	UNIT_NASSERT(InfNormLessThan(Vec4(1.f, 6.f, 3.f, 4.f), 5.f));
	UNIT_NASSERT(InfNormLessThan(Vec4(1.f, 2.f, 6.f, 4.f), 5.f));
	UNIT_NASSERT(InfNormLessThan(Vec4(1.f, 2.f, 3.f, 6.f), 5.f));

	UNIT_NASSERT(InfNormLessThan(Vec4(-6.f, 2.f, 3.f, 4.f), 5.f));
	UNIT_NASSERT(InfNormLessThan(Vec4(1.f, -6.f, 3.f, 4.f), 5.f));
	UNIT_NASSERT(InfNormLessThan(Vec4(1.f, 2.f, -6.f, 4.f), 5.f));
	UNIT_NASSERT(InfNormLessThan(Vec4(1.f, 2.f, 3.f, -6.f), 5.f));
}

UNIT_TEST("INIT", "Mat4") {
	Math::Mat4 m;

	for(size_t i = 0; i < 16; ++i) {
		switch(i) {
		case 0:
		case 5:
		case 10:
		case 15:
			UNIT_ASSERT(m.data[i] == 1.f);
			break;

		default:
			UNIT_ASSERT(m.data[i] == 0.f);
			break;
		}
	}
}
