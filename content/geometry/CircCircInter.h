/**
 * Author: Lucian Bicsi
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes the intersection(s) between two circles.
 * Can be 0(non-intersecting), 1(tangent), or 2 points.
 * Status: somewhat tested
 */
#pragma once

#include "Circle.h"

void CircleCircleIntersect(Circle c, Circle d,
                           vector<Point>& inter) {
  Point a = c.c, b = d.c, delta = b - a;
  double r1 = c.r, r2 = d.r;
  if (sgn(abs(delta)) == 0) return;
  double r = r1 + r2, d2 = norm(delta);
  double p = (d2 + r1 * r1 - r2 * r2) / (2.0 * d2);
  double h2 = r1 * r1 - p * p * d2;
  if (sgn(d2 - r * r) > 0 || sgn(h2) < 0) return;
  Point mid = a + delta * p,
        per = perp(delta) * sqrt(abs(h2) / d2);
  inter.push_back(mid - per);
  if (sgn(abs(per)) != 0)
    inter.push_back(mid + per);
}