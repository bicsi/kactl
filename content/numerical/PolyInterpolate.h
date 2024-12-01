/**
 * Author: Simon Lindholm
 * Date: 2017-05-10
 * License: CC0
 * Source: Wikipedia
 * Description: Given $n$ points $(x[i], y[i])$, computes an $n-1$-degree polynomial $p$ that
 *  passes through them: $p(x) = a[0]*x^0 + ... + a[n-1]*x^{n-1}$.
 *  For numerical precision, pick $x[k] = c*\cos(k/(n-1)*\pi), k=0 \dots n-1$.
 * Time: O(n^2)
 */
#pragma once

using Poly = vector<double>;
Poly Interpolate(Poly x, Poly y) {
  int n = x.size();
  Poly res(n), temp(n);
  for (int i = 0; i < n; ++i)
  for (int j = i + 1; j < n; ++j)
    y[j] = (y[j] - y[i]) / (x[j] - x[i]);
  double last = 0; temp[0] = 1;
  for (int i = 0; i < n; ++i)
  for (int j = 0; j < n; ++j) {
    res[j] += y[i] * temp[j];
    swap(last, temp[j]);
    temp[j] -= last * x[i];
  }
  return res;
}
