/**
 * Author: Lucian Bicsi
 * Source: Wikipedia
 * Description: Recovers any n-order linear recurrence
 * relation from the first 2*n terms of the recurrence.
 * Very useful for guessing linear recurrences after
 * brute-force / backtracking the first terms.
 * Should work on any field. Numerical stability for
 * floating-point calculations is not guaranteed.
 * Usage: BerlekampMassey({0, 1, 1, 3, 5, 11}) => {1, 2}
 */
#include <bits/stdc++.h>
#include "ModOps.h"

using namespace std;

vector<ModInt> BerlekampMassey(vector<ModInt> s) {
  int n = s.size();
  vector<ModInt> C(n, 0), B(n, 0);
  C[0] = B[0] = 1;
  
  ModInt b = 1; int L = 0;
  for (int i = 0, m = 1; i < n; ++i) {
    /// Calculate discrepancy
    ModInt d = s[i];
    for (int j = 1; j <= L; ++j)
      d = d + C[j] * s[i - j];
    
    if (d.get() == 0) { ++m; continue; }
    
    /// C -= d / b * B * x^m
    auto T = C; ModInt coef = d * inv(b);
    for (int j = m; j < n; ++j)
      C[j] = C[j] - coef * B[j - m];
    
    if (2 * L > i) { ++m; continue; }
    
    L = i + 1 - L; B = T; b = d; m = 1;
  }
  
  C.resize(L + 1); C.erase(C.begin());
  for (auto& x : C) x = ModInt(0) - x;
  
  return C;
}
