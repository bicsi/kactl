/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: Bunicul
 * Description: A slow, albeit very easy-to-implement
 * flow algorithm.
 * Time: O(EF) where $E$ is the number of edges and F is the
 * maximum flow.
 * Status: works
 */
#pragma once

struct EZFlow {
  vector<vector<int>> G;
  vector<bool> vis;
  int t;
  
  EZFlow(int n) : G(n), vis(n) {}
  
  bool dfs(int node) {
    if (node == t) return true;
    vis[node] = true;
    
    for (auto& vec : G[node]) {
      if (!vis[vec] && dfs(vec)) {
        G[vec].push_back(node);
        swap(vec, G[node].back());
        G[node].pop_back();
        return true;
      }
    }
    return false;
  }
  
  void AddEdge(int a, int b) { G[a].push_back(b); }
  int ComputeFlow(int s, int t) {
    this->t = t; int ans = 0;
    while (dfs(s)) {++ans; fill(vis.begin(),vis.end(), false);}
    return ans;
  }
};
