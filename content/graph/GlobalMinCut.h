/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook, http://www.cs.tau.ac.il/~zwick/grad-algo-08/gmc.pdf
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * PRECONDITION: W[i][j] = W[j][i], W[i][i] = 0.
 * Time: O(V^3), optimizable to O(VE \log{E}) (use heap at (*))
 * Status: Lightly tested
 */
#pragma once

pair<int, vector<bool>> GlobalMinCut(vector<vector<int>> W) {
  int n = W.size(), best = 2e9;
  vector<bool> cut(n), best_cut, vis;

  for (int phase = n - 1; phase > 0; phase--) {
    vector<int> deg = W[0]; 
    int prev, cur = 0;
    vis = cut;
    for (int i = 0; i < phase; ++i) {
      prev = cur; cur = -1;
      for (int j = 1; j < n; ++j) // (*)
        if (!vis[j] && (cur == -1 || deg[j] > deg[cur])) 
          cur = j;
      if (i == phase - 1) {
        for (int j = 0; j < n; ++j) W[prev][j] += W[cur][j];
        for (int j = 0; j < n; ++j) W[j][prev] = W[prev][j];
        cut[cur] = true;
        if (deg[cur] < best) 
          best = deg[cur], best_cut = cut;
      } else {
        for (int j = 0; j < n; ++j) 
          deg[j] += W[cur][j]; // (*)
        vis[cur] = true;
      }
    }
  }
  return {best, best_cut};
}