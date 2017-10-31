/**
 * Author: Lucian Bicsi
 * Date: 2009-04-09
 * License: CC0
 * Source: Basic geometry
 * Description: Returns true iff p lies on the line segment from s to e. Intended for use with e.g. Point<long long> where overflow is an issue. Use (SegDist(s, e, p) < kEps) instead when using Point<double>.
 * Status:
 */
#pragma once

#include "Point.h"

bool OnSegment(Point s, Point e, Point p) {
	Point ds = p - s, de = p - e;
	return cross(ds, de) == 0 && dot(ds, de) <= 0;
}
