/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:
 Checks if two lines intersect, and returns 1 if one intersection,
 0 if lines are parallel (no intersection), and -1 if they coincide
 (infinite intersections).
 * Status: tested
 */
#pragma once

#include "Point.h"

int LineIntersection(Point a, Point b, Point p, Point q) {
  double c1 = det(a, b, p), c2 = det(a, b, q);
  if (sgn(c1 - c2)) return 1;
  if (sgn(c1) == 0) return -1;
  return 0;
}
