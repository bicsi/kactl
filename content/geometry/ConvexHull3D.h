/**
 * Author: Lucian Bicsi
 * Date: 2020-12-07
 * Source: derived from https://codeforces.com/blog/entry/81768
 * Description: Incrementally computes all faces of the 
 * 3-dimension hull of a point set.
 * \textbf{Ideally, no four points must be coplanar}, 
 * or else random results will be returned.
 * All faces will point outwards. To optimize, cache cross 
 * products. For integer coordinates, products of up to $X^{3}$
 * are made.
 * Time: O(N^2)
 * Status: tested on SPOJ CH3D, kattis starsinacan
 */

#pragma once

#include "Point3D.h"

vector<Face> Hull3D(vector<Point> P) {
  int n = P.size(); assert(n >= 3);
  vector<vector<bool>> dead(n, vector<bool>(n));
  vector<Face> ret = {{0, 1, 2}, {2, 1, 0}}, nret;
  for (int i = 3; i < n; ++i) {
    nret.clear();
    for (auto f : ret) {
      auto [a, b, c] = f;
      if (det(P[a], P[b], P[c], P[i]) > 0) // consider sgn() 
        dead[a][b] = dead[b][c] = dead[c][a] = true;
      else nret.push_back(f);
    }
    ret.clear();
    for (auto f : nret) {
      ret.push_back(f);
      for (int j = 0, k = 2; j < 3; k = j++) {
        int a = f[k], b = f[j];
        if (dead[b][a]) ret.push_back({b, a, i});
        dead[b][a] = false;
      }
    }
  }
  return ret;
}