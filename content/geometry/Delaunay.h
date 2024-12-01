/**
 * Author: Mattias de Zalenski, Lucian Bicsi
 * Date: Unknown
 * Description: Computes the Delaunay triangulation of a set of points.
 * Triangles are in counter-clockwise order. Answer is unique if 
 * the set of points is in general position. Products are up to $O(X^4)$.
 * Time: O(N^2)
 * Status: stress-tested
 */
#pragma once

#include "ConvexHull3D.h"

vector<array<int, 3>> Delaunay(vector<Point> P) {
  int n = P.size();
  vector<D3::Point> Q(n);
  for (int i = 0; i < n; ++i)
    Q[i] = {P[i].real(), P[i].imag(), norm(P[i])};
  vector<array<int, 3>> ret;
  for (auto [a, b, c] : D3::Hull3D(Q)) 
    if (D3::det(Q[a], Q[b], Q[c], {0, 0, 1}) < 0)
      ret.push_back({a, b, c});
  return ret;
}