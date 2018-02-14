/**
 * Author: Lukas Polacek
 * Date: 2010-01-26
 * License: CC0
 * Source: TopCoder tutorial
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for large $c$.
 * Time: O(64/bits \cdot \log b), where $bits = 64-k$, if we want to deal with
 * $k$-bit numbers.
 */
#pragma once

typedef unsigned long long ull;
const int bits = 10;
// if all numbers are less than 2^k, set bits = 64-k
const ull po = 1 << bits;
ull ModMul(ull a, ull b, ull &c) {
	ull x = a * (b & (po - 1)) % c;
	while ((b >>= bits) > 0) {
		a = (a << bits) % c;
		x += (a * (b & (po - 1))) % c;
	}
	return x % c;
}
ull ModPow(ull a, ull b, ull mod) {
	if (b == 0) return 1;
	ull res = ModPow(a, b / 2, mod);
	res = ModMul(res, res, mod);
	if (b & 1) return ModMul(res, a, mod);
	return res;
}
