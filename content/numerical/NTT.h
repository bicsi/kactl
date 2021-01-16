/**
 * Author: Lucian Bicsi
 * Date: 2020-11-28
 * License: CC0
 * Source: based on https://github.com/kmyk/competitive-programming-library
 * Description: Cooley-Tukey-like ntt. 
 * Discrete Fourier modulo specific nice primes of the form 
 * $2^a b+1$, where the convolution result has size at 
 * most $2^a$. 
 * Takes around 100ms on $N = 5 \cdot 10^5$ on library-checker.
 * Time: $O(N \log N)$
 * Status: stress-tested
 */
#pragma once

#include "../number-theory/ModInt.h"

void DFT(vector<ModInt> &a, bool rev) {
  int n = a.size(); ModInt g = 1; // assert(!(n & (n - 1)));
  for (; g.pow((MOD - 1) / 2) == 1; g = g + 1);
  if (rev) g = g.inv();

  vector<ModInt> b(n);
  for (int step = n / 2; step; step /= 2) {
    ModInt w = g.pow((MOD - 1) / (n / step)), wn = 1; 
    for (int i = 0; i < n; i += 2 * step) {
      for (int j = 0; j < step; ++j) {
        auto u = a[i + j], v = wn * a[i + j + step];
        b[i / 2 + j] = u + v; b[(i + n) / 2 + j] = u - v;
      }
      wn = wn * w;
    }
    swap(a, b);
  }
  if (rev) {
    auto n1 = ModInt(n).inv();
    for (auto& x : a) x = x * n1;
  }
}
