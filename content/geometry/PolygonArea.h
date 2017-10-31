/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Status: Tested with unitTest, Kattis problems polygonarea and wrapping and UVa Online Judge Problem: 109 - SCUD Busters
 */
#pragma once

#include "Point.h"

double SignedArea(const vector<Point> &P) {
  double area = cross(P.back(), P.front());
  for (int i = 1; i < (int)P.size(); ++i)
    area += cross(P[i - 1], P[i]);
  return area; // Divide by 2 for proper area
}
