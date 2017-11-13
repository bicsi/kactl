/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source:
 * Description: A class for simulating the rotating calipers
 * technique. Calipers will rotate covering the smallest arc.
 * To change that, edit the code at (*) to add 2*kPi if
 * return value is < 0
 */
#pragma once
#include "Point.h"

struct Caliper {
  Point pivot; double angle;
  
  double AngleTo(Point oth) {
    double new_ang = arg(oth - pivot);
    return remainder(new_ang - angle, 2.0 * kPi); // (*)
  }
  
  void RotateCCW(double ang) { angle += ang; }
  void ChangePivot(Point oth) { pivot = oth; }
  
  // Need to have same angle
  double DistanceTo(Caliper oth) {
    Point a = RotateCCW(pivot, -angle);
    Point b = RotateCCW(oth.pivot, -angle);
    return abs(a.imag() - b.imag());
  }
};

