/**
 * Author: Lucian Bicsi
 * Date: 2004-02-08
 * License: CC0
 * Description: Converts matrix to reduced row-echelon form.
 * Each of the first $r$ rows will have exactly one non-zero
 * column $piv_i$, and all columns to the left of $piv_i$ will
 * be zero.
 * To compute rank, do \texttt{RowEchelon(M).size()}.
 * Time: O(M^2 N)
 * Status: tested
 */
#pragma once

using ld = double;
using mat = vector<vector<ld>>;
const ld EPS = 1e-9;

vector<int> RowEchelon(mat& A) {
  int n = A.size(), m = A[0].size(); 
  ld coef; vector<int> piv;
  for (int i = 0, rnk = 0; i < m && rnk < n; ++i) {
    for (int j = rnk + 1; j < n; ++j) 
      if (abs(A[j][i]) > abs(A[rnk][i]))
        swap(A[j], A[rnk]);
    if (abs(coef = A[rnk][i]) < EPS) continue;
    for (int j = 0; j < m; ++j) A[rnk][j] /= coef;
    for (int j = 0; j < n; ++j) {
      if (j == rnk || abs(coef = A[j][i]) < EPS) continue;
      for (int k = 0; k < m; ++k)
        A[j][k] -= coef * A[rnk][k];
    }
    piv.push_back(i); ++rnk;
  }
  return piv;
}