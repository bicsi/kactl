/**
 * Author: Simon Lindholm
 * Date: 2015-02-11
 * License: CC0
 * Source: Wikipedia
 * Description: Fast integration using an adaptive Simpson's rule.
 * Usage:
  double z, y;
  double h(double x) { return x*x + y*y + z*z <= 1; }
  double g(double y) { ::y = y; return Quad(h, -1, 1); }
  double f(double z) { ::z = z; return Quad(g, -1, 1); }
  double sphere_vol = Quad(f, -1, 1), pi = sphere_vol * 3 / 4;
 */
#pragma once

template<typename Func>
double recurse(Func f, double a, double b,
               double eps, double S) {
  auto simpson = [&](double a, double b) {
    return (f(a) + 4 * f((a + b) / 2) + f(b)) * (b - a) / 6; };
  double c = (a + b) / 2;
  double S1 = simpson(a, c), S2 = simpson(c, b);
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
