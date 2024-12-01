/**
 * Author: Lucian Bicsi
 * Date: 2004-02-08
 * License: CC0
 * Description: Computes the inverse of an $N \times N$ matrix.
 * Returns true if successful. 
 * For inverse modulo prime powers,
 * repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\
 * (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of $A$ modulo $p$, and $k$ is doubled in each step.
 * Time: O(N^3)
 * Status: tested
 */
#pragma once

#include "RowEchelon.h"

bool Invert(mat& A) {
  int n = A.size(); // assert(n == A[0].size()); 
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      A[i].push_back(i == j);
  auto [piv, sgn] = RowEchelon(A);
  if ((int)piv.size() < n || piv.back() >= n) return false;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j)
      // For adjunct, do A[i][j + n] *= sgn instead.
      A[i][j + n] /= A[i][i]; 
    A[i].erase(A[i].begin(), A[i].begin() + n);
  }
  return true;
}