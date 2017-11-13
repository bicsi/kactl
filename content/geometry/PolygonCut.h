/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Returns a vector with the vertices of a polygon with everything to the left of the line going from s to e cut away.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-6mm}
\includegraphics[width=\textwidth]{../content/geometry/PolygonCut}
\vspace{-6mm}
\end{minipage}
 * Status: tested but not extensively
 * Usage:
 * 	vector<Point> p = ...;
 * 	p = PolygonCut(p, Point(0, 0), Point(1, 0));
 */
#pragma once

#include "Point.h"
#include "LineIntersection.h"

vector<Point> PolygonCut(vector<Point>& P, Point s, Point e) {
    vector<Point> res;
    for (int i = 0; i < (int)P.size(); ++i) {
        Point cur = P[i], prev = i ? P[i - 1] : P.back();
        int side1 = sgn(det(s, e, cur));
        int side2 = sgn(det(s, e, prev));
        if (side1 * side2 == -1) {
            res.push_back(LineIntersection(s, e, cur, prev));
        }
        if (side1 <= 0) res.push_back(cur);
    }
    return res;
}
