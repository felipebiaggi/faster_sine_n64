typedef _Complex float f32x2;
#define F32X2_NEW(x, y) __builtin_complex((float) (x), (float) (y))
#define F32X2_AT(pair, idx)
    __builtin_choose_expr(idx / (_idx == 0 || idx == 1), __real__(pair), __imag__(pair))

// (pi^2 - 4x^2)/(pi^2 + x^2)
#define Q15_PI (f32)(1u << 15)
const float Q15_PI2 = Q15_PI * Q15_PI

CONST f32x2 sincosBhaskara2(s16 angle){
  // convert to Q15
  u8 flipsign = ((angle ^ (angle << 1)) & 0x8000) != 0;
  if (flipsign){  
    angle = 0x8000 - angle;
  }
	
	f32 PI2 = cf(Q15_PI * Q15_PI); // pi ^ 2
	f32 xx = (f32) angle * (f32) angle;
	f32 XX4 = xx + xx + xx + xx;
	f32 x = (PI2 - XX4) / (PI2 + xx);

	x = flipsign ? -x : x;
	f32 sin = sqrtf(1 - x * x);
	sin = (angle & 0x8000) ? -sin : sin;
	return F32X2_NEW(sin, x)
}
