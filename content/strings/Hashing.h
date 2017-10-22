/**
 * Author: Simon Lindholm
 * Date: 2015-03-15
 * License: CC0
 * Source: own work
 * Description: Arithmetic mod 2^64-1. 5x slower than mod 2^64
 * and more code, but works on evil test data
 * (e.g. Thue-Morse).
 * Status: tested
 */
#pragma once

struct K {
  using H = uint64_t;
  using H2 = __uint128_t;
  H x; K(H x = 0) : x(x) {}
  K operator+(K o){ return x + o.x + H(((H2)x + o.x)>>64); }
  K operator*(K o){ return K(x*o.x)+ H(((H2)x * o.x)>>64); }
  H operator-(K o) { K a = *this + ~o.x; return a.x + !~a.x; }
};


