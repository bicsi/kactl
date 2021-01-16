/**
 * Author: Lucian Bicsi
 * Date: 2020-12-07
 * Description: Computes the (signed) volume of a polyhedron. 
 * Faces should point outwards.
 * Status: tested
 */
#pragma once

T Volume(vector<Point> v, vector<Face> faces) {
  double ret = 0; Point O{0, 0, 0}; // origin
  for (auto [a, b, c] : faces) ret += det(v[c], v[b], v[a], O);
  return ret / 6;
}
