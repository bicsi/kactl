/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: Basic math
 * Description:\\
\begin{minipage}{75mm}
Returns the signed distance between point p and the line containing points a and b. Positive value on left side and negative on right as seen from a towards b. a==b gives nan, although don't rely on that. Also works in 3D. It uses products in intermediate steps so watch out for overflow if using int or long long. Using Point3D will always give a non-negative distance.
\end{minipage}
\begin{minipage}{15mm}
\includegraphics[width=\textwidth]{../content/geometry/LineDistance}
\end{minipage}
 * Status: tested 
 */
#pragma once

#include "Point.h"

double lineDist(Point a, Point b, Point p) {
	return det(a, b, p) / dist(a, b);
}
