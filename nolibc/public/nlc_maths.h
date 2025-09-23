#ifndef NOLIBC_NLC_MATHS_H
#define NOLIBC_NLC_MATHS_H

#define Min(a, b)			((a) < (b)	? (a) : (b))
#define Max(a, b)			((a) > (b)	? (a) : (b))
#define Clamp(x, lo, hi)	((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

#endif //NOLIBC_NLC_MATHS_H