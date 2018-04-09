/**
 * Author: Lucian Bicsi
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes the intersection between two circles
 * and other circle-related geometry
 * Status: somewhat tested
 */
#pragma once

#include "Circle.h"

// Computes the intersection of two circles.
// Can be 0(non-intersecting), 1(tangent), or 2 points
void CircleCircleIntersect(Circle c, Circle d,
                           vector<Point>& inter) {
  Point a = c.c, b = d.c, delta = b - a;
  double r1 = c.r, r2 = d.r;
  if (sgn(norm(delta)) == 0) return;
  double r = r1 + r2, d2 = norm(delta);
  double p = (d2 + r1 * r1 - r2 * r2) / (2.0 * d2);
  double h2 = r1 * r1 - p * p * d2;
  if (sgn(d2 - r * r) > 0 || sgn(h2) < 0) return;
  Point mid = a + delta * p,
        per = perp(delta) * sqrt(abs(h2) / d2);
  inter.push_back(mid - per);
  if (sgn(per) != 0)
    inter.push_back(mid + per);
}

// Computes the intersection between a line pq and a circle
// Can be 0(non-intersecting), 1(tangent), or 2 points
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
