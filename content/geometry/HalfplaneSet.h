/**
 * Author: Lucian Bicsi
 * Date: 2018-05-01
 * License: CC0
 * Source: Basic geometry
 * Description: Data structure that dynamically keeps track
 * of the intersection of halfplanes. Use is straigntforward.
 * Area should be able to be kept dynamically with some
 * modifications.
 *
 * NOTE: REMOVE t LOGIC FROM ANGLE WHEN IMPLEMENTING
 * Time: O(\log n)
 * Status: tested on infoarena and codechef
 * Usage:
 *  HalfplaneSet hs;
 *  hs.Cut({0, 0}, {1, 1});
 *  double best = hs.Maximize({1, 2});
 */
#pragma once

#include "Point.h"
#include "LineIntersection.h"
#include "Angle.h"

struct HalfplaneSet : multimap<Angle, Point> {
  using Iter = multimap<Angle, Point>::iterator;
  
  HalfplaneSet() {
    insert({{+1, 0}, {-kInf, -kInf}});
    insert({{0, +1}, {+kInf, -kInf}});
    insert({{-1, 0}, {+kInf, +kInf}});
    insert({{0, -1}, {-kInf, +kInf}});
  }
  
  Iter get_next(Iter it) {
    return (next(it) == end() ? begin() : next(it)); }
  Iter get_prev(Iter it) {
    return (it == begin() ? prev(end()) : prev(it)); }
  Iter fix(Iter it) { return it == end() ? begin() : it; }
  
  // Cuts everything to the RIGHT of a, b
  // For LEFT, just swap a with b
  void Cut(Angle a, Angle b) {
    if (empty()) return;
    int old_size = size();
    
    auto eval = [&](Iter it) {
      return sgn(det(a.p(), b.p(), it->second)); };
    auto intersect = [&](Iter it)  {
      return LineIntersection(a.p(), b.p(),
          it->second, it->first.p() + it->second);
    };
    
    auto it = fix(lower_bound(b - a));
    if (eval(it) >= 0) return;
    
    while (size() && eval(get_prev(it)) < 0)
      fix(erase(get_prev(it)));
    while (size() && eval(get_next(it)) < 0)
      it = fix(erase(it));
    
    if (empty()) return;
    
    if (eval(get_next(it)) > 0) it->second = intersect(it);
    else it = fix(erase(it));
    if (old_size <= 2) return;
    it = get_prev(it);
    insert(it, {b - a, intersect(it)});
    if (eval(it) == 0) erase(it);
  }
  
  // Maximizes dot product
  double Maximize(Angle c) {
    assert(!empty());
    auto it = fix(lower_bound(c.t90()));
    return dot(it->second, c.p());
  }
  
  double Area() {
    if (size() <= 2) return 0;
    double ret = 0;
    for (auto it = begin(); it != end(); ++it)
      ret += cross(it->second, get_next(it)->second);
    return ret;
  }
};
