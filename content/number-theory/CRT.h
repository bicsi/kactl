/**
 * Author: Mattias de Zalenski, Per Austrin, Lukas Polacek
 * Date: 2003-02-16
 * Description: Chinese Remainder Theorem.
 *
 * Solves a system of equations of type $x = b_{i} (mod p_{i})$.
 * For not coprime $n, m$, use \texttt{ChineseCommon}.
 * Note that all numbers must be less than
 * $2^{31}$ if you have Z = unsigned long long.
 * Status: Works
 * Time: $\log(m + n)$
 */
#pragma once

#include "Euclid.h"

template<typename LL>
LL CRT(int cnt, vector<int> p, vector<int> b) {
  LL N = 1, ans = 0; int k = p.size();
  for (int i = 0; i < k; ++i) N *= p[i];
  for (int i = 0; i < k; ++i) {
    LL mult = (ModInv(N / p[i], p[i]) * (N / p[i])) % N;
    mult = (mult * b[i]) % N;
    ans += mult; ans %= N;
  }
  if (ans < 0) ans += N;
  return ans;
}

template <class Z>
Z ChineseCommon(Z a, Z m, Z b, Z n) {
	Z d = gcd(m, n);
	if (((b -= a) %= n) < 0) b += n;
	if (b % d) return -1; // No solution
	return d * chinese(Z(0), m/d, b/d, n/d) + a;
}
