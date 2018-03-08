/**
 * Author: Lucian Bicsi
 * Date: 2018-02-26
 * License: CC0
 * Source: Own
 * Description: Determines the voronoi cell of a point with
 * a list of other points. If the cell is unbounded, check
 * for points with very high coordinates.
 * Status: Tested by eye
 * Time: O(N^{2})
 */
#pragma once

#include "Point.h"
#include "PolygonCut.h"
#include <bits/stdc++.h>

using namespace std;

const double kInf = 1e9;

// To the right of mediator is region closer to b
pair<Point, Point> Mediator(Point a, Point b) {
  Point m = (a + b) * .5;
  return make_pair(m, m + perp(b - a));
}

vector<Point> VoronoiCell(Point p, vector<Point> P) {
  vector<Point> ret = {{-kInf, -kInf}, {kInf, -kInf},
    {kInf, kInf}, {-kInf, kInf}};
  
  for (auto oth : P) {
    Point a, b; tie(a, b) = Mediator(p, oth);
    ret = PolygonCut(ret, b, a);
  }
  return ret;
}

