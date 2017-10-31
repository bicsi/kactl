/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-22
 * License: CC0
 * Source: Basic geometry
 * Description: Returns true if p lies within the polygon described by the points between iterators begin and end. Returns 0 if on polygon, 1 if inside polygon and -1 if outside. Answer is calculated by counting the number of intersections between the polygon and a line going from p to infinity in the positive x-direction. The algorithm uses products in intermediate steps so watch out for overflow. If points within epsilon from an edge should be considered as on the edge replace the line "if (onSegment..." with the comment bellow it (this will cause overflow for int and long long).
 * Time: O(n)
 * Status: tested with unitTest and Kattis problems copsrobbers, pointinpolygon and intersection
 * Usage:
 * 	typedef Point<int> pi;
 * 	vector<pi> v; v.push_back(pi(4,4));
 * 	v.push_back(pi(1,2)); v.push_back(pi(2,1));
 * 	bool in = insidePolygon(v.begin(),v.end(), pi(3,4), false);
 */
#pragma once

#include "Point.h"
#include "OnSegment.h"
#include "SegmentDistance.h"

template <class It>
int InsidePolygon(It begin, It end, const Point& p) {
	int n = 0; //number of isects with line from p to (inf, p.y)
	for (It i = begin, j = end-1; i != end; j = i++) {
		//if p is on edge of polygon
		if (OnSegment(*i, *j, p)) return 0;
		//or: if (SegDist(*i, *j, p) <= kEps) return 0;
		//increment n if segment intersects line from p
		n += (max(i->y(), j->y()) > p.y() &&
          min(i->y(), j->y()) <= p.y() &&
          (det(*i, *j, p) > 0) == (i->y() <= p.y()));
	}
  return n % 2 ? 1 : -1; //inside if odd number of intersections
}
