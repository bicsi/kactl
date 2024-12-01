/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
Returns the signed distance between point p and the line containing points a and b. 
Positive value on left side and negative on right as seen from $a$ towards $b$. 
Does products up to $O(X^3)$.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/lineDistance}
\end{minipage}
 * Warning: If $a=b$ nan is returned, although don't rely on that. 
 * Status: tested
 */
#pragma once

#include "Point.h"

double LineDistance(Point a, Point b, Point p) {
	return det(a, b, p) / abs(b - a);
}
// Projects point p on line (a, b)
Point ProjectPointOnLine(Point p, Point a, Point b) {
  return a + (b - a) * dot(p - a, b - a) / norm(b - a);
}
