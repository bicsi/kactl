/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/montgomery_multiplication.html
 * Description: Faster ModInt multiplication using Montgomery space. Copy other
 * operators from "ModInt.h" if needed.
 * Status: Tested
 * Warning: Using the ModInt wrapper might make the operations slower.
 * Refactor at your own risk.
 */
#pragma once

// Set T2 such that (T2)mod * mod does not overflow.
using T = uint32_t;
using T2 = uint64_t;
const int BITS = 8 * sizeof(T); // = 32
const T MOD = 998244353, INV = 3296722945, R2 = 932051910;
//            970592641         905457281       670047489
//           1000000007        2068349879       582344008 
//     3006703054056749 11535267960557300389  886200325609766
//  1000000000000000003 14584756025394899627 527506668952824130
   
T reduce(T2 x) {
  T q = (T)x * INV, a = (x - (T2)q * MOD) >> BITS;
  if (a >= MOD) a += MOD; // not a mistake
  return a;
}
T mul(T a, T b) { return reduce((T2)a * b); }
// Only required for unknown modulo. Call before everything.
void init(T mod) {
  MOD = mod; INV = 1; R2 = -mod % mod;
  for (int i = 1; i < BITS; i *= 2)
    INV *= 2 - MOD * INV;
  for (int i = 0; i < 4; i++) 
    if ((R2 *= 2) >= mod) 
      R2 -= mod;
  for (int i = 4; i < BITS; i *= 2)
    R2 = mul(R2, R2);
}

struct ModInt {
  T x;
  ModInt(T x) : x(mul(x, R2)) {}
  ModInt ctr(T x) { // unsafe internal constructor
    if (x >= MOD) x -= MOD;
    ModInt ret(*this); ret.x = x; return ret;
  }
  ModInt operator+(ModInt oth) { return ctr(x + oth.x); }
  ModInt operator-(ModInt oth) { return ctr(x + MOD - oth.x); }
  ModInt operator*(ModInt oth) { return ctr(mul(x, oth.x)); } 
  T Get() { return reduce(x); }
};