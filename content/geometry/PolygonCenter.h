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
	auto i = P.begin(), j = prev(P.end());
	Point res{0.0, 0.0}; double area = 0.0;
	for (; i != P.end(); j=i++) {
		res += (*i + *j) * cross(*j, *i);
		area += cross(*j, *i);
	}
	return res / area / 3.0;
}
