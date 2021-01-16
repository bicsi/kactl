/**
 * Author: Lucian Bicsi
 * Date: 2020-11-28
 * License: CC0
 * Source: https://cp-algorithms.com/algebra/polynomial.html
 * Description: Fast polynomial division/remainder.
 * Time: $O(N \log N)$
 * Status: tested manually
 */
#pragma once

#include "PolyMul.h"
#include "PolyInv.h"

vector<ModInt> Div(vector<ModInt> a, vector<ModInt> b) { 
  int d = (int)a.size() - (int)b.size() + 1;
  if (d <= 0) return {};
  reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
  a.resize(d); b.resize(d);
  auto ret = Mul(a, Inv(b, d));
  ret.resize(d);
  reverse(ret.begin(), ret.end());
  return ret;
}

vector<ModInt> Rem(vector<ModInt> a, vector<ModInt> b) {
  auto sub = Mul(Div(a, b), b); 
  for (int i = 0; i < (int)sub.size(); ++i)
    a[i] = a[i] - sub[i];
  while (a.size() && a.back() == 0) a.pop_back();
  return a;
}
