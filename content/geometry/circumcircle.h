/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-11
 * License: CC0
 * Source: http://en.wikipedia.org/wiki/Circumcircle
 * Description:\\
\begin{minipage}{75mm}
The circumcirle of a triangle is the circle intersecting all three vertices. CircumRadius returns the radius of the circle going through points a, b and c and CircumCenter returns the center of the same circle.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-2mm}
\includegraphics[width=\textwidth]{../content/geometry/Circumcircle}
\end{minipage}
 * Status: tested
 */
#pragma once

#include "Circle.h"

double CircumRadius(Point a, Point b, Point c) {
  return dist(a, b) * dist(b, c) * dist(c, a) /
    abs(det(a, b, c)) / 2.;
}
Point CircumCenter(Point a, Point b, Point c) {
  c -= a; b -= a;
  return a + perp(c*norm(b) - b*norm(c)) / cross(c, b) / 2.;
}
Circle CircumCircle(Point a, Point b, Point c) {
  Point p = CircumCenter(a, b, c);
  return {p, abs(p - a)};
}
