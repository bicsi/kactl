/**
 * Author: Victor Lecomte, chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description: Returns true iff p lies on the line segment from s to e.
 * Use \texttt{(segDist(s,e,p)<=epsilon)} instead when using Point<double>.
 * Status:
 */
#pragma once

#include "Point.h"

bool OnSegment(P s, P e, P p) {
  return sgn(det(p, s, e)) == 0 && sgn(dot(s - p, e - p)) <= 0;
}