/**
 * Author: Lucian Bicsi
 * Date: 2021-09-23
 * License: CC0
 * Source:
 * Description: Computes the center of mass of a polygon.
 **/
#pragma once
#include "Point.h"

Point PolygonCenter(vector<Point> P) {
  int n = P.size();
  Point O = 0.; ld A = 0.;
  for (int i = 0, j = n - 1; i < n; j = i++) {
    O += (P[i] + P[j]) * cross(P[j], P[i]);
    A += cross(P[j], P[i]);
  }
  O = O / 3. / A;
  return O;
}