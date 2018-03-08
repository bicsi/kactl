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
\includegraphics[width=\textwidth]{../content/geometry/SegmentDistance}
\end{minipage}
 * Status: NOT TESTED
 * Usage: 
 * 	Point a{0, 0}, b{2, 2}, p{1, 1};
 * 	bool onSegment = SegmentDistance(p, a, b) < kEps;
 */
#pragma once

#include "Point.h"

double SegmentDistance(Point p, Point a, Point b) {
	if (a == b) return abs(p - a); // Beware of precision!!!
  double d = norm(b - a);
  double t = min(d, max(.0, dot(p - a, b - a)));
	return abs((p - a) * d - (b - a) * t) / d;
}

// Projects point p on segment [a, b]
Point ProjectPointOnSegment(Point p, Point a, Point b) {
  double d = norm(b - a);
  if (d == 0) return a; // Beware of precision!!!
  
  double r = dot(p - a, b - a) / d;
  return (r < 0) ? a : (r > 1) ? b : (a + (b - a) * r);
}
