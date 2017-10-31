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
 * Status: tested
 * Usage: 
 * 	Point a{0, 0}, b{2, 2}, p{1, 1};
 * 	bool onSegment = segDist(a, b, p) < kEps;
 */
#pragma once

#include "Point.h"

double SegDist(Point s, Point e, Point p) {
	if (s == e) return dist(p, s); // Beware of precision!!!
	double t = min(d, max(.0, det(s, p, e)));
	return dist((p - s) * d, (e - s) * t) / norm(e - s);
}
