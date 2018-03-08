/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Point declaration, and basic operations.
 * Status: Works fine, used a lot
 */
#pragma once

using Point = complex<double>;

const double kPi = 4.0 * atan(1.0);
const double kEps = 1e-9; // Good eps for long double is ~1e-11

#define X() real()
#define Y() imag()

double dot(Point a, Point b) { return (conj(a) * b).X(); }
double cross(Point a, Point b) { return (conj(a) * b).Y(); }
double dist(Point a, Point b) { return abs(b - a); }
Point perp(Point a) { return Point{-a.Y(), a.X()}; } // +90deg

double rotateCCW(Point a, double theta) {
  return a * polar(1.0, theta); }
double det(Point a, Point b, Point c) {
  return cross(b - a, c - a); }

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

