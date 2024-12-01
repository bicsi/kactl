/**
 * Author: Lucian Bicsi
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes the intersection(s) between a line pq and a circle.
 * Can be 0(non-intersecting), 1(tangent), or 2 points
 * Status: somewhat tested
 */
#pragma once

#include "Circle.h"
#include "LineDistance.h"

void LineCircleIntersect(Circle c, Point p, Point q,
                         vector<Point>& inter) {
  Point mid = ProjectPointOnLine(c.c, p, q);
  double d2 = norm(mid - c.c), dist = c.r * c.r - d2;
  if (sgn(dist) < 0) return;
  Point dir = (q - p) * sqrt(dist) / abs(q - p);
  inter.push_back(mid - dir);
  if (sgn(dist) != 0)
    inter.push_back(mid + dir);
}
