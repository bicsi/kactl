/**
 * Author: Lucian Bicsi
 * Date: 2020-11-28
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/polynomial.html
 * Description: Computes $\bar{a}$ s.t. $deg(\bar{a})=n, a \bar{a} = 1 (\text{mod } X^n)$.
 * Time: $O(N \log N)$
 * Status: tested manually
 */
#pragma once

#include "NTT.h"

vector<ModInt> Inv(vector<ModInt> a, int n) {
  vector<ModInt> ret(1, a[0].inv()), tmp;
  for (auto& x : a) x = x * (-1);
  for (int step = 2; step < n * 2; step *= 2) {
    tmp = a; tmp.resize(4 * step, 0); ret.resize(4 * step, 0);
    DFT(tmp, 0); DFT(ret, 0);
    for (int i = 0; i < 4 * step; ++i)
      ret[i] = (ret[i] * tmp[i] + 2) * ret[i];
    DFT(ret, 1);
    ret.resize(step);
  }
  ret.resize(n);
  return ret;
}