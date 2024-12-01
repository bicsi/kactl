/**
 * Author: Lucian Bicsi
 * Date: 2020-11-28
 * License: CC0
 * Source: based on https://github.com/kmyk/competitive-programming-library
 * Description: Computes $c[x + y] \mathrel{{+}{=}} a[x] \cdot b[y]$.
 * To optimize, consider having extra logic for the case where
 * a == b.
 * Time: $O(N + M \log (N + M))$
 * Status: stress-tested
 */
#pragma once

#include "NTT.h"

vector<ModInt> Mul(vector<ModInt> a, vector<ModInt> b) {
  if (a.empty() || b.empty()) return {};
  int m = a.size() + b.size() - 1, n = m;
  while (n & (n - 1)) ++n;
  a.resize(n, 0); b.resize(n, 0);
  DFT(a, 0); DFT(b, 0);
  for (int i = 0; i < n; ++i)
    a[i] = a[i] * b[i];
  DFT(a, 1); a.resize(m);
  return a;
}
