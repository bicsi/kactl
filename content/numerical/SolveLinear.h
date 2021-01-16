/**
 * Author: Lucian Bicsi
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $Mx = b$. Set $A$ to be the block matrix
 * $[M|b]$. If there are multiple solutions,
 * returns a solution which has all free variables set to 0.
 * Time: O(M^2 N)
 * Status: tested
 */
#pragma once
#include "RowEchelon.h"

vector<ld> SolveLinear(mat& A) {
  int m = A[0].size() - 1;
  auto piv = RowEchelon(A);
  if (piv.size() > m) return {};
  vector<ld> sol(m, 0.);
  for (int i = 0; i < (int)piv.size(); ++i)
    sol[piv[i]] = A[i][m];
  return sol;
}