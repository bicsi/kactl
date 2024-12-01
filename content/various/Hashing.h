/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Arithmetic mod $2^{64}-1$. 2x slower than mod $2^{64}$ and more
 * code, but works on evil test data (e.g. Thue-Morse, where
 * ABBA... and BAAB... of length $2^{10}$ hash the same mod $2^{64}$).
 * "typedef ull H;" instead if you think test data is random,
 * or work mod $10^9+7$ if the Birthday paradox is not a problem.
 * Status: stress-tested
 */
#pragma once

struct H {
	typedef uint64_t ull;
	ull x; H(ull x=0) : x(x) {}
#define OP(O,A,B) H operator O(H o) { ull r = x; asm \
	(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
	OP(+,,"d"(o.x)) OP(*,"mul %1\n", "r"(o.x) : "rdx")
	H operator-(H o) { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
