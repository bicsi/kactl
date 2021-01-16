/**
 * Author: Stanford
 * Source: Stanford Notebook
 * License: MIT
 * Description: Solves a general linear maximization problem: maximize $c^T x$ subject to $Ax \le b$, $x \ge 0$.
 * Returns -INF if there is no solution, INF if there are arbitrarily good solutions, or the maximum value of $c^T x$ otherwise.
 * The input vector is set to an optimal $x$ (or in the unbounded case, an arbitrary solution fulfilling the constraints).
 * Numerical stability is not guaranteed. For better performance, define variables such that $x = 0$ is viable.
 * Usage:
 * A = {{1,-1}, {-1,1}, {-1,-2}};
 * b = {1,1,-4}, c = {-1,-1}, x;
 * T val = LPSolver(A, b, c).Solve(x);
 * Time: O(NM * \#pivots), where a pivot may be e.g. an edge relaxation. O(2^n) in the general case.
 * Status: seems to work?
 */
#pragma once

using T = double; // long double, Rational, double + mod<P>...
using vec = vector<T>;
using mat = vector<vec>;

const T EPS = 1e-8, INF = 1/.0;
#define MT make_tuple
#define FOR(i, a, b) for(int i = (a); i < (b); ++i)

double Simplex(mat A, vec b, vec c, vec& x) {
  int m = b.size(), n = c.size();
  vector<int> N(n + 1), B(m); 
  mat D(m + 2, vec(n + 2));

  FOR (i, 0, m) FOR (j, 0, n) D[i][j] = A[i][j];
  FOR (i, 0, m) B[i] = n + i, D[i][n] = -1, D[i][n + 1] = b[i];
  FOR (j, 0, n) N[j] = j, D[m][j] = -c[j];
  N[n] = -1, D[m + 1][n] = 1;

  auto pivot = [&](int r, int s) {
    vec& a = D[r]; T inv = 1. / a[s];
    FOR (i, 0, m + 2) if (i != r && abs(D[i][s]) > EPS) {
      vec& b = D[i]; T inv2 = b[s] * inv;
      FOR (j, 0, n + 2) b[j] -= a[j] * inv2;
      b[s] = a[s] * inv2;
    }
    FOR (j, 0, n + 2) if (j != s) D[r][j] *= inv;
    FOR (i, 0, m + 2) if (i != r) D[i][s] *= -inv;
    D[r][s] = inv;
    swap(B[r], N[s]);
  };
  auto simplex = [&](int phase) {
    int x = m + phase - 1;
    while (true) {
      auto T = MT(INF, -1, -1);
      FOR (j, 0, n + 1) if (N[j] != -phase) 
        T = min(T, MT(D[x][j], N[j], j));
      if (get<0>(T) > -EPS) return true;
      int s = get<2>(T); T = MT(INF, -1, -1);
      FOR (i, 0, m) {
        if (D[i][s] < EPS) continue;
        T = min(T, MT(D[i][n + 1] / D[i][s], B[i], i));
      }
      int r = get<2>(T); 
      if (r == -1) return false;
      pivot(r, s);
    }
  };
  int r = 0;
  FOR (i, 1, m) if (D[i][n + 1] < D[r][n + 1]) r = i;
  if (D[r][n + 1] < -EPS) {
    pivot(r, n);
    if (!simplex(2) || D[m + 1][n + 1] < -EPS) return -INF;
    FOR (i, 0, m) if (B[i] == -1) {
      auto T = MT(INF, -1, -1);
      FOR (j, 0, n + 1) T = min(T, MT(D[i][j], N[j], j));
      pivot(i, get<2>(T));
    }
  }
  bool ok = simplex(1); x.assign(n, 0);
  FOR (i, 0, m) if (B[i] < n) x[B[i]] = D[i][n + 1];
  return ok ? D[m][n + 1] : INF;
}