/**
 * Author: Per Austrin, Ulf Lundstrom
 * Date: 2009-04-09
 * License: CC0
 * Source: https://vlecomte.github.io/cp-geo.pdf
 * Description:\\
\begin{minipage}{75mm}
 Apply the affine transformation (translation, rotation and scaling) 
 which maps $(p, q) \rightarrow (fp, fq)$ to point $r$.
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

Point LinTrans(Point p, Point q, Point fp, Point fq, Point r) { 
    return fp + (r - p) * (fq - fp) / (q - p);
}