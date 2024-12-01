/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Simple integration of a function over an interval using
 *  Simpson's rule. According to cp-algorithms, the error is
 * $-\frac{1}{90} (\frac{b-a}{2})^5 f^{(4)}(\xi)$ for some $\xi \in [a, b]$.
 * Status: mostly untested
 */
#pragma once

template<typename Func>
double Quad(Func f, double a, double b) {
  const int n = 1000;
  double h = (b - a) / 2 / n;
  double v = f(a) + f(b);
  for (int i = 1; i < 2 * n; ++i)
    v += f(a + i * h) * (i & 1 ? 4 : 2);
  return v * h / 3;
}
