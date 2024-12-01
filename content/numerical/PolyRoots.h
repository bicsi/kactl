/**
 * Author: Lucian Bicsi
 * Date: 2020-11-28
 * License: CC0
 * Source: https://en.wikipedia.org/wiki/Durand–Kerner_method
 * Description: Durand-Kerner method of finding all roots of polynomial.
 * If polynomial has real coefficients, it might make more sense to 
 * initialize roots with conjugate pairs (and potentially one 
 * real root), see (*). It might not converge for all polynomials
 * and all sets of initial roots.
 * Time: $O(N^2)$ per iteration
 * Status: tested by hand
 */
#pragma once

using C = complex<double>;

vector<C> FindRoots(vector<C> p) {
  int n = p.size() - 1;
  vector<C> ret(n);
  for (int i = 0; i < n; ++i) 
    ret[i] = pow(C{0.456, 0.976}, i); // (*)
  for (int it = 0; it < 1000; ++it) {
    for (int i = 0; i < n; ++i) {
      C up = 0, dw = 1;
      for (int j = n; j >= 0; --j) {
        up = up * ret[i] + p[j];
        if (j != i && j != n) 
          dw = dw * (ret[i] - ret[j]);
      }
      ret[i] -= up / dw / p[n];
    }
  }
  return ret;
}
