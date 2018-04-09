/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Returns the intersection between non-parallel lines.
 If unsure if lines are concurrent, check with LineIntersectionCheck.
 
 The wrong position will be returned if P is complex<int> and the intersection point does not have integer coordinates. Products of three coordinates are used in intermediate steps so watch out for overflow if using int or long long.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/lineIntersection}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"

Point LineIntersection(Point a, Point b, Point p, Point q) {
  double c1 = det(a, b, p), c2 = det(a, b, q);
  assert(sgn(c1 - c2)); // undefined if parallel
  return (q * c1 - p * c2) / (c1 - c2);
}
