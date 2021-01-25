/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns the shortest distance between point p and the line segment from point s to e.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-10mm}
\includegraphics[width=\textwidth]{content/geometry/SegmentDistance}
\end{minipage}
 * Status: NOT TESTED
 * Usage: 
 * 	Point a{0, 0}, b{2, 2}, p{1, 1};
 * 	bool onSegment = SegmentDistance(p, a, b) < EPS;
 */
#pragma once

#include "Point.h"

double SegmentDistance(Point p, Point a, Point b) {
  if (sgn(abs(a - b))) return abs(p - a);
  double d = norm(b - a), t = clamp(dot(p - a, b - a), 0., d);
  return abs((p - a) * d - (b - a) * t) / d;
}
// Projects point p on segment [a, b]
Point ProjectPointOnSegment(Point p, Point a, Point b) {
  double d = norm(b - a);
  if (sgn(d) == 0) return a;
  double r = dot(p - a, b - a) / d;
  return (r < 0) ? a : (r > 1) ? b : (a + (b - a) * r);
}
