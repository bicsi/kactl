/**
 * Author: Lucian Bicsi
 * Date: 2004-02-08
 * License: CC0
 * Description: Neat trick to compute
 * $\displaystyle c[x \vert y] \mathrel{{+}{=}} a[x] \cdot b[y]$,
 * where $x$ and $y$ satisfy $x \& y = 0$. Use with "OR" FST transform.
 * The idea is to do FST convolutions and discard the results unless the 
 * number of bits of the result equals the sums of the bits of the
 * multiplicants. The idea can probably be adapted to other similar problems.
 * Time: O(N \log^2{N}) (around 2s for $N = 2^{20}$)
 * Status: tested on library-checker.
 */
#pragma once 

#include "FST.h"

using Poly = vector<int>;

Poly SubsetConv(Poly a, Poly b) {
  int n = a.size(), lg = 31 - __builtin_clz(n);
  assert(n == (1 << lg));
  vector<Poly> p(lg + 1, Poly(n, 0)), q(p);
  for (int i = 0; i < n; ++i) {
    int lev = __builtin_popcount(i);
    p[lev][i] = a[i]; q[lev][i] = b[i];
  }
  for (int i = 0; i <= lg; ++i) DFT(p[i], 0), DFT(q[i], 0);
  for (int i = 0; i <= lg; ++i) {
    fill(b.begin(), b.end(), 0);
    for (int j = 0; j <= i; ++j)
      for (int k = 0; k < n; ++k)
        b[k] = b[k] + p[j][k] * q[i - j][k];
    DFT(b, 1);
    for (int j = 0; j < n; ++j)
      if (__builtin_popcount(j) == i)
        a[j] = b[j];
  }
  return a;
}