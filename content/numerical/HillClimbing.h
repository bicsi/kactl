/**
 * Author: Simon Lindholm
 * Date: 2015-02-04
 * License: CC0
 * Source: Johan Sannemo
 * Description: Poor man's optimization for unimodal functions.
 * Finds minimum of a function func[Point] => double.
 * To change with maximum, change the comparison at (*)
 * Status: used with great success
 */
#pragma once

struct Point { double x, y; };

template<typename Func>
pair<double, Point> HillClimb(Point p, Func func) {
  double best = func(p);
  
  for (double step = 1e9; step > 1e-20; step /= 2)
    for (int it = 0; it < 100; ++it)
      for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy) {
          Point q = p; q.x += dx * step; q.y += dy * step;
          double now = func(q);
          if (best > now) { best = now; p = q; } // (*)
        }
  return make_pair(best, p);
}
