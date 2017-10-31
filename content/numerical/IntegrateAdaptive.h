/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Fast integration using an adaptive Simpson's rule.
 * Status: mostly untested
 * Usage:
	double z, y;
	double h(double x) { return x*x + y*y + z*z <= 1; }
	double g(double y) { ::y = y; return Quad(h, -1, 1); }
	double f(double z) { ::z = z; return Quad(g, -1, 1); }
	double sphereVol = Quad(f, -1, 1), pi = sphereVol*3/4;
 */
#pragma once

template<typename Func>
double simpson(Func f, double a, double b) {
	double c = (a + b) / 2;
	return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}

template<typename Func>
double recurse(Func f, double a, double b,
               double eps, double S) {
	double c = (a + b) / 2;
	double S1 = simpson(f, a, c);
  double S2 = simpson(f, c, b);
  double T = S1 + S2;
	if (abs(T - S) < 15 * eps || b - a < 1e-10)
		return T + (T - S) / 15;
	return recurse(f, a, c, eps / 2, S1) +
         recurse(f, c, b, eps / 2, S2);
}

template<typename Func>
double Quad(Func f, double a, double b, double eps = 1e-8) {
	return recurse(f, a, b, eps, simpson(f, a, b));
}
