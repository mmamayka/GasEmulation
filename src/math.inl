namespace Math {
	inline Vec4::Vec4(float filler) noexcept
	{$$
		ASSERT(std::isfinite(filler));

		__m128 freg = _mm_load_ss(&filler);
		__m128 dreg = _mm_shuffle_ps(freg, freg, AUX::SSE_ShufMask<0, 0, 0, 1>);
		_mm_store_ps(this->data, dreg);

		MATH_VEC4_ASSERT(*this);
	}

	inline Vec4::Vec4(float x, float y, float z, float w) noexcept
	{$$
		ASSERT(std::isfinite(x));
		ASSERT(std::isfinite(y));
		ASSERT(std::isfinite(z));
		ASSERT(std::isfinite(w));

		_mm_store_ps(this->data, _mm_set_ps(w, z, y, x));

		MATH_VEC4_ASSERT(*this);
	}

	inline Vec4::Vec4(const Vec4& v) noexcept {
		MATH_VEC4_ASSERT(v);

		_mm_store_ps(data, _mm_load_ps(v.data));

		MATH_VEC4_ASSERT(*this);
	}

	inline Vec4 const& Vec4::operator= (Vec4 const& v) noexcept {
		MATH_VEC4_ASSERT(v);

		_mm_store_ps(data, _mm_load_ps(v.data));

		MATH_VEC4_ASSERT(*this);

		return *this;
	}

	inline Vec4 const& Vec4::operator+= (Vec4 const& v) noexcept {
		MATH_VEC4_ASSERT(*this);
		MATH_VEC4_ASSERT(v);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vint  = _mm_load_ps(v.data);
		__m128 result = _mm_add_ps(vthis, vint);
		_mm_store_ps(this->data, result);

		MATH_VEC4_ASSERT(*this);

		return *this;
	}

	inline Vec4 const& Vec4::operator-= (Vec4 const& v) noexcept {
		MATH_VEC4_ASSERT(*this);
		MATH_VEC4_ASSERT(v);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vint  = _mm_load_ps(v.data);
		__m128 result = _mm_sub_ps(vthis, vint);
		_mm_store_ps(this->data, result);
		
		MATH_VEC4_ASSERT(*this);

		return *this;
	}

	inline Vec4 const& Vec4::operator*= (float v) noexcept {
		MATH_VEC4_ASSERT(*this);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vmul  = _mm_set_ps1(v);
		__m128 result = _mm_mul_ps(vthis, vmul);
		_mm_store_ps(this->data, result);

		MATH_VEC4_ASSERT(*this);

		return *this;
	}

	inline Vec4 const& Vec4::operator/= (float v) noexcept {
		MATH_VEC4_ASSERT(*this);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vmul  = _mm_set_ps1(v);
		__m128 result = _mm_div_ps(vthis, vmul);
		_mm_store_ps(this->data, result);

		MATH_VEC4_ASSERT(*this);
		return *this;
	}

	inline float const Vec4::sqlen() const noexcept {
		MATH_VEC4_ASSERT(*this);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vsq   = _mm_mul_ps(vthis, vthis);
		__m128 vhsum = _mm_hadd_ps(vsq, vsq);
		__m128 vsum  = _mm_hadd_ps(vhsum, vhsum);

		float result = NAN;
		_mm_store_ps(&result, vsum);

		ASSERT(std::isfinite(result));

		return result;
	}
	inline float const Vec4::len() const noexcept {
		MATH_VEC4_ASSERT(*this);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vsq   = _mm_mul_ps(vthis, vthis);
		__m128 vhsum = _mm_hadd_ps(vsq, vsq);
		__m128 vsqsum= _mm_hadd_ps(vhsum, vhsum);
		__m128 vsum  = _mm_sqrt_ss(vsqsum);

		float result = NAN;
		_mm_store_ps(&result, vsum);

		ASSERT(std::isfinite(result));

		return result;
	}
	inline float const Vec4::ilen() const noexcept {
		MATH_VEC4_ASSERT(*this);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vsq   = _mm_mul_ps(vthis, vthis);
		__m128 vhsum = _mm_hadd_ps(vsq, vsq);
		__m128 vsqsum= _mm_hadd_ps(vhsum, vhsum);

		// bad precision for EPS = 1e-6
		// __m128 vsum  = _mm_rsqrt_ss(vsqsum);
		__m128 vsum = _mm_sqrt_ps(vsqsum);

		__m128 ones = _mm_set1_ps(1.f);
		__m128 vlen = _mm_div_ps(ones, vsum);

		float result = NAN;
		_mm_store_ps(&result, vlen);

		ASSERT(std::isfinite(result));

		return result;
	}
	inline float const Vec4::isqlen() const noexcept {
		MATH_VEC4_ASSERT(*this);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vsq   = _mm_mul_ps(vthis, vthis);
		__m128 vhsum = _mm_hadd_ps(vsq, vsq);
		__m128 vsqsum= _mm_hadd_ps(vhsum, vhsum);

		// bad precision for EPS = 1e-6
		// __m128 vsum  = _mm_rcp_ss(vsqsum);
		__m128 ones = _mm_set1_ps(1.f);
		__m128 vsum = _mm_div_ps(ones, vsqsum);

		float result = NAN;
		_mm_store_ss(&result, vsum);

		ASSERT(std::isfinite(result));

		return result;
	}

	inline void Vec4::norm() noexcept {
		MATH_VEC4_ASSERT(*this);

		__m128 vthis = _mm_load_ps(this->data);
		__m128 vsq   = _mm_mul_ps(vthis, vthis);
		__m128 vhsum = _mm_hadd_ps(vsq, vsq);
		__m128 vsqsum= _mm_hadd_ps(vhsum, vhsum);

		// bas precision for EPS = 1e-6
		// __m128 vislen= _mm_rsqrt_ss(vsqsum);
		__m128 vislen= _mm_sqrt_ss(vsqsum);
		__m128 vilen = _mm_shuffle_ps(vislen, vislen, 0x0);
		// __m128 vres  = _mm_mul_ps(vthis, vilen);
		__m128 vres  = _mm_div_ps(vthis, vilen);
		_mm_store_ps(this->data, vres);

		MATH_VEC4_ASSERT(*this);
	}

	inline void Vec4::refl(Vec4 const& normal) noexcept {
		*this -= 2 * Dot(*this, normal) * normal;
	}
	inline void Vec4::reflu(Vec4 const& normal) noexcept {
		*this -= 2 * Dot(*this, normal) * normal / normal.sqlen();
	}
	// 208АК 495 408 42 27

	inline bool const operator== (Vec4 const& x, Vec4 const& y) noexcept {
		__m128 xreg = _mm_load_ps(x.data);
		__m128 yreg = _mm_load_ps(y.data);
		__m128 difreg = _mm_sub_ps(xreg, yreg);

		__m128 absreg = AUX::SSE_Abs(difreg);

		__m128 epsreg = _mm_set1_ps(EPS);
		__m128 cmpreg = _mm_cmpgt_ps(absreg, epsreg);

		return !_mm_movemask_ps(cmpreg);
	}

	inline bool const Vec4::isZero() const noexcept {
		__m128 dreg = _mm_load_ps(data);

		__m128 absreg = AUX::SSE_Abs(dreg);

		__m128 epsreg = _mm_set1_ps(EPS);
		__m128 cmpreg = _mm_cmpgt_ps(absreg, epsreg);

		return !_mm_movemask_ps(cmpreg);
	}

	// will be inlined
	inline bool const operator!= (Vec4 const& x, Vec4 const& y) noexcept {
		return !(x == y);
	}

	inline Vec4 const operator+ (Vec4 const& x, Vec4 const& y) noexcept {
		__m128 xreg = _mm_load_ps(x.data);
		__m128 yreg = _mm_load_ps(y.data);
		__m128 sreg = _mm_add_ps(xreg, yreg);
		return Vec4(sreg);
	}

	inline Vec4 const operator- (Vec4 const& x, Vec4 const& y) noexcept {
		__m128 xreg = _mm_load_ps(x.data);
		__m128 yreg = _mm_load_ps(y.data);
		__m128 sreg = _mm_sub_ps(xreg, yreg);
		return Vec4(sreg);
	}

	inline Vec4 const operator* (Vec4 const& x, float y) noexcept {
		__m128 xreg = _mm_load_ps(x.data);
		__m128 yreg = _mm_set1_ps(y);
		__m128 mreg = _mm_mul_ps(xreg, yreg);
		return Vec4(mreg);
	}

	// strange additional command, see disasm
	inline Vec4 const operator/ (Vec4 const& x, float y) noexcept {
		__m128 xreg = _mm_load_ps(x.data);
		__m128 yreg = _mm_set1_ps(y);
		__m128 mreg = _mm_div_ps(xreg, yreg);
		return Vec4(mreg);
	}

	inline float const Dot(Vec4 const& a, Vec4 const& b) noexcept {
		MATH_VEC4_ASSERT(a);
		MATH_VEC4_ASSERT(b);

		__m128 va = _mm_load_ps(a.data);
		__m128 vb = _mm_load_ps(b.data);
		__m128 vm = _mm_mul_ps(va, vb);
		__m128 vh = _mm_hadd_ps(vm, vm);
		__m128 vs = _mm_hadd_ps(vh, vh);

		float res = NAN;
		_mm_store_ss(&res, vs);

		ASSERT(std::isfinite(res));

		return res;
	}

	inline Vec4 const Cross(Vec4 const& a, Vec4 const& b) noexcept {
		__m128 areg = _mm_load_ps(a.data);
		__m128 breg = _mm_load_ps(b.data);

		__m128 at1reg = _mm_shuffle_ps(areg, areg, 
			(1 << 0) | (2 << 2) | (0 << 4) | (3 << 6));

		__m128 at2reg = _mm_shuffle_ps(areg, areg,
			(2 << 0) | (0 << 2) | (1 << 4) | (3 << 6));

		__m128 bt1reg = _mm_shuffle_ps(breg, breg,
			(2 << 0) | (0 << 2) | (1 << 4) | (3 << 6));

		__m128 bt2reg = _mm_shuffle_ps(breg, breg,
			(1 << 0) | (2 << 2) | (0 << 4) | (3 << 6));

		__m128 m2reg = _mm_mul_ps(at2reg, bt2reg);
		__m128 resreg = _mm_fmsub_ps(at1reg, bt1reg, m2reg);

		return Vec4(resreg);
	}
}

