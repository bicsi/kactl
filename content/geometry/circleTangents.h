/**
 * Author: Ulf Lundstrom
 * Date: 2009-04-06
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
Returns a pair of the two points on the circle with radius r centered around c whose tangent lines intersect p. If p lies within the circle NaN-points are returned. The first point is the one to the right as seen from the p towards c.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/CircleTangents}
\end{minipage}
 * Status: tested on petrozavodsk winter 2018
 * Usage:
 * 	auto p = Tangents(Point(100, 2), Point(0, 0), 2);
 */
#pragma once

#include "Circle.h"

pair<Point, Point> Tangents(Point p, Circle c) {
  p -= c.c;
  double x = c.r * c.r / norm(p), y = sqrt(x - x * x);
  return make_pair(c.c + p * x + perp(p) * y,
                   c.c + p * x - perp(p) * y);
}
