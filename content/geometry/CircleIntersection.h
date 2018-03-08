/**
 * Author: Simon Lindholm
 * Date: 2015-09-01
 * License: CC0
 * Description: Computes the intersection between two circles
 * Returns duplicate point when tangent
 * Status: somewhat tested
 */
#pragma once

#include "Point.h"

#include <bits/stdc++.h>

struct Circle { Point c; double r; };

vector<Point> CircleIntersection(Circle& A, Circle& B) {
  Point a = A.c, b = B.c;
  double r1 = A.r, r2 = B.r;
  Point delta = b - a;
  if (abs(delta) < kEps) return {};
  double r = r1 + r2, d2 = norm(delta);
  double p = (d2 + r1*r1 - r2*r2) / (2.0 * d2);
  double h2 = r1*r1 - p*p*d2;
  if (d2 > r*r + kEps || h2 < -kEps) return {};
  Point mid = a + delta * p,
        per = perp(delta) * sqrt(abs(h2) / d2);
  return {mid - per, mid + per};
}
