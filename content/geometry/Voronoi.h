/**
 * Author: Lucian Bicsi
 * Date: 2018-02-26
 * License: CC0
 * Source: Own
 * Description: Determines the voronoi cell of a point with
 * a list of other points. to see if the cell is unbounded, check
 * for points with very high coordinates.
 * Status: Tested by eye
 * Time: $O(N^{2})$ technically, but expect $O(N M)$, where 
 * $M$ is size of output.
 */
#pragma once

#include "Point.h"
#include "PolygonCut.h"

const double INF = 1e9;

// To the right of mediator is region closer to b
pair<Point, Point> Mediator(Point a, Point b) {
  Point m = (a + b) * .5;
  return make_pair(m, m + perp(b - a));
}
vector<Point> VoronoiCell(Point p, vector<Point> P) {
  vector<Point> ret = {{-INF, -INF}, {+INF, -INF}, 
                       {+INF, +INF}, {-INF, +INF}};
  for (auto q : P) {
    if (p == q) continue;
    auto [a, b] = Mediator(p, q);
    ret = PolygonCut(ret, b, a);
  }
  return ret;
}
