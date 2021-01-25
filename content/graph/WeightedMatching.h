/**
 * Author: blatul on infoarena
 * Date: Unknown
 * Source: https://infoarena.ro/job_detail/1781287?action=view-source
 * Description: Simplified Jonker-Volgenant algorithm for assignment problem.
 * Negate costs for max cost.
 * Time: O(N^3), fast in practive
 * Status: tested on infoarena cmcm.
 */
#pragma once

template <typename T>
T MinAssignment(const vector<vector<T>>& W) {
  int n = W.size(), m = W[0].size();       // assert(n <= m);
  vector<T> v(m), dist(m);                 // v: potential
  vector<int> L(n, -1), R(m, -1);          // matching pairs
  vector<int> idx(m), prev(m);
  iota(idx.begin(), idx.end(), 0);
  
  auto residue = [&](int i, int j) { return W[i][j] - v[j]; };
  for (int f = 0; f < n; ++f) {
    for (int j = 0; j < m; ++j) 
      dist[j] = residue(f, j), prev[j] = f;
    T w; int j, l, s = 0, t = 0;
    while (true) {
      if (s == t) {
        l = s; w = dist[idx[t++]];
        for (int k = t; k < m; ++k) {
          j = idx[k]; T h = dist[j];
          if (h <= w) {
            if (h < w) t = s, w = h; 
            idx[k] = idx[t]; idx[t++] = j;
          }
        }
        for (int k = s; k < t; ++k) {
          j = idx[k]; 
          if (R[j] < 0) goto aug;
        }
      }
      int q = idx[s++], i = R[q];
      for (int k = t; k < m; ++k) {
        j = idx[k];
        T h = residue(i, j) - residue(i, q) + w;
        if (h < dist[j]) {
          dist[j] = h; prev[j] = i;
          if (h == w) {
            if (R[j] < 0) goto aug;
            idx[k] = idx[t]; idx[t++] = j;
          }
        }
      }
    }
  aug:
    for (int k = 0; k < l; ++k) v[idx[k]] += dist[idx[k]] - w;
    for (int i = -1; i != f;;)
      R[j] = i = prev[j], swap(j, L[i]);
  }
  T ret = 0;
  for (int i = 0; i < n; ++i) 
    ret += W[i][L[i]]; // (i, L[i]) is a solution
  return ret;
}
