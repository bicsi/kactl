/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook, http://www.cs.tau.ac.il/~zwick/grad-algo-08/gmc.pdf
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * Time: O(V^3)
 * Status: Lightly tested
 */
#pragma once
#include <bits/stdc++.h>

using namespace std;

using T = long long;
pair<T, vector<int>> GetMinCut(vector<vector<T>> weights) {
  int n = weights.size();
  vector<int> used(n), best_cut, cut;
  T best_weight = numeric_limits<T>::max();

  for (int phase = n - 1; phase > 0; phase--) {
    auto w = weights[0];
    auto added = used;
    int prev, k = 0;

    for (int i = 0; i < phase; ++i) {
      prev = k; k = -1;

      for (int j = 1; j < n; ++j)
        if (!added[j] && (k == -1 || w[j] > w[k])) 
          k = j;

      if (i != phase - 1) {
        for (int j = 0; j < n; ++j)
          w[j] += weights[k][j];
        added[k] = true;
        continue;
      }
      
      for (int j = 0; j < n; ++j) 
          weights[prev][j] += weights[k][j];
      for (int j = 0; j < n; ++j) 
          weights[j][prev] = weights[prev][j];
      
      used[k] = true; cut.push_back(k);
      
      if (w[k] < best_weight) {
        best_cut = cut;
        best_weight = w[k];
      } 
    }
  }
  return {best_weight, best_cut};
}
