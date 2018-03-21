/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Simple integration of a function over an interval using
 *  Simpson's rule. The error should be proportional to $h^4$, although in
 *  practice you will want to verify that the result is stable to desired
 *  precision when epsilon changes.
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
