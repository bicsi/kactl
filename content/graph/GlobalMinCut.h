/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook, http://www.cs.tau.ac.il/~zwick/grad-algo-08/gmc.pdf
 * Description: Find a global minimum cut in an undirected graph, as represented by an adjacency matrix.
 * Time: O(V^3), optimizable to O(VE \log{E}) (with heap)
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
      for (int j = 1; j < n; ++j) 
        if (!vis[j] && (cur == -1 || deg[j] > deg[cur])) 
          cur = j;
      vis[cur] = true;
      for (int j = 0; j < n; ++j) if (!vis[j])
        deg[j] += W[cur][j]; 
    }
    if (deg[cur] < best) best = deg[cur], best_cut = cut;
    for (int j = 0; j < n; ++j)
      W[prev][j] += W[cur][j], W[j][prev] += W[j][cur];
    cut[cur] = true;
  }
  return {best, best_cut};
}