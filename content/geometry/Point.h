/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Point declaration, and basic operations.
 * Status: Works fine, used a lot
 */
#pragma once

using Point = complex<double>;

const double PI = 4.0 * atan(1.0);
const double EPS = 1e-9; // Good eps for long double is ~1e-11

int sgn(double d) { return (d > EPS) - (d < -EPS); }

double dot(Point a, Point b) { 
  return a.real() * b.real() + a.imag() * b.imag(); }
double cross(Point a, Point b) { 
  return a.real() * b.imag() - a.imag() * b.real(); }
double det(Point a, Point b, Point c) { 
  return cross(b - a, c - a); }
double dist(Point a, Point b) { return abs(b - a); }
Point perp(Point a) { return {-a.imag(), a.real()}; } // +90deg
Point rotate_ccw(Point a, double theta) {
  return a * polar(1.0, theta); }

namespace std {
  bool operator<(const Point a, const Point b) {
    return make_pair(a.real(), a.imag()) < 
      make_pair(b.real(), b.imag());
  }
}
// abs() is norm (length) of vector
// norm() is square of abs()
// arg() is angle of vector
// det() is twice the signed area of the triangle abc
// and is > 0 iff c is to the left as viewed from a towards b.
// polar(r, theta) gets a vector from abs() and arg()

void ExampleUsage() {
  Point a{1.0, 1.0}, b{2.0, 3.0};
  cerr << a << " " << b << endl;
  cerr << "Length of ab is: " << dist(a, b) << endl;
  cerr << "Angle of a is: " << arg(a) << endl;
  cerr << "axb is: " << cross(a, b) << endl;
}