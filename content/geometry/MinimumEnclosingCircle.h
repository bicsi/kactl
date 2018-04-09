/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: NAPC 2017 solution presentation
 * Description: Computes the minimum circle that encloses a set of points.
 * Time: expected O(n)
 * Status: fuzz-tested
 */
#pragma once

#include "Circumcircle.h"

// IMPORTANT: random_shuffle(pts.begin(), pts.end())
Circle MEC(vector<Point>& pts, vector<Point> ch = {}) {
  if (pts.empty() || ch.size() == 3) {
    switch (ch.size()) {
      case 0: return {0, -1};
      case 1: return {ch[0], 0};
      case 2: return {(ch[0] + ch[1])/2, abs(ch[0] - ch[1])/2};
      case 3: return CircumCircle(ch[0], ch[1], ch[2]);
      default: assert(false);
    }
  }
  
  auto p = pts.back(); pts.pop_back();
  auto c = MEC(pts, ch);
  if (sgn(abs(p - c.c) - c.r) > 0) {
    ch.push_back(p);
    c = MEC(pts, ch);
  }
  pts.push_back(p);
  return c;
}

