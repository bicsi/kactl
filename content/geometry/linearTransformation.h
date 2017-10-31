/**
 * Author: Per Austrin, Ulf Lundstrom
 * Date: 2009-04-09
 * Source:
 * Description:\\
\begin{minipage}{75mm}
 Apply the affine transformation (translation, rotation and scaling) which takes line (p0, p1) to line (q0, q1) to point r.
\end{minipage}
\begin{minipage}{15mm}
\vspace{-8mm}
\includegraphics[width=\textwidth]{../content/geometry/LinearTransformation}
\vspace{-2mm}
\end{minipage}
 * Status: not tested
 */
#pragma once

#include "Point.h"

Point LinearTransformation(Point p0, Point p1,
                           Point q0, Point q1, Point r) {
  Point dp = p1 - p0, dq = q1 - q0,
        num = dp * conj(dq);
  return q0 + (r - p0) * conj(num) / norm(dp);
}
