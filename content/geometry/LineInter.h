/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
 Returns the intersection between non-parallel lines.
 Does products up to $O(X^3)$. Both vector variant and line
 variant are present.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-5mm}
\includegraphics[width=\textwidth]{content/geometry/lineIntersection}
\vspace{-2mm}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Point.h"
#include "Line.h"

Point LineIntersection(Point a, Point b, Point p, Point q) {
  double c1 = det(a, b, p), c2 = det(a, b, q);
  assert(sgn(c1 - c2)); // undefined if parallel
  return (q * c1 - p * c2) / (c1 - c2);
}

tuple<T4, T4, T2> LineIntersection(Line m, Line n) {
  T2 d = (T2)m.a * n.b - (T2)m.b * n.a; // assert(d);
  T4 x = (T4)m.c * n.b - (T4)m.b * n.c; 
  T4 y = (T4)m.a * n.c - (T4)m.c * n.a;
  return {x, y, d}; // (x/d, y/d) is intersection. 
}