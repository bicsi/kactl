/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: Wikipedia
 * Description: Recovers any $n$-order linear recurrence relation from the first
 * $2n$ terms of the recurrence.
 * Useful for guessing linear recurrences after brute-forcing the first terms.
 * Should work on any field, but numerical stability for floats is not guaranteed.
 * Output will have size $\le n$.
 * Usage: BerlekampMassey({0, 1, 1, 3, 5, 11}) // {1, 2}
 * Time: O(N^2)
 * Status: bruteforce-tested mod 5 for n <= 5 and all s
 */
#pragma once

#include "../number-theory/ModInt.h"

vector<ModInt> BerlekampMassey(vector<ModInt> s) {
  int n = s.size();
  vector<ModInt> C(n, 0), B(n, 0);
  C[0] = B[0] = 1;

  auto b = C[0]; int L = 0;
  for (int i = 0, m = 1; i < n; ++i) {
    /// Calculate discrepancy
    auto d = s[i];
    for (int j = 1; j <= L; ++j)
      d = d + C[j] * s[i - j];
    if (d == 0) { ++m; continue; }
    /// C -= d / b * B * X^m
    auto T = C; auto coef = d / b;
    for (int j = m; j < n; ++j)
      C[j] = C[j] - coef * B[j - m];
    if (2 * L > i) { ++m; continue; }
    L = i + 1 - L; B = T; b = d; m = 1;
  }
  C.resize(L + 1); C.erase(C.begin());
  for (auto& x : C) x = x * (-1);
  return C;
}