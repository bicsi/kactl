/**
 * Author: Lucian Bicsi
 * Date: 2021-01-27
 * License: CC0
 * Description: Computes the determinant of $N \times N$ matrix.
 * Time: O(N^3)
 * Status: NOT TESTED
 */
#pragma once

#include "RowEchelon.h"

ld Determinant(mat& A) {
  int n = A.size(); 
  ld det = RowEchelon(A).second;
  for (int i = 0; i < n; ++i) 
    det *= A[i][i];
  return det;
}