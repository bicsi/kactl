/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-08
 * License: CC0
 * Source:
 * Description: Returns the center of mass for a polygon.
 * Status: Tested
 */
#pragma once

#include "Point.h"

Point PolygonCenter(vector<Point>& P) {
  int n = P.size(); Point res{0, 0}; double area = 0;
  for (int i = 0, j = n - 1; i < n; j = i++) {
		res += (P[i] + P[j]) * cross(P[j], P[i]);
		area += cross(P[j], P[i]);
	}
	return res / area / 3.0;
}
