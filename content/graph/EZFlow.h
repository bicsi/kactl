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
  vector<bool> Vis;
  int s, t;
  
  EZFlow(int n) : G(n), Vis(n) {}
  
  bool dfs(int node) {
    if (node == t) return true;
    Vis[node] = true;
    
    for (auto& vec : G[node]) {
      if (!Vis[vec] && dfs(vec)) {
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
    this->s = s; this->t = t; int ans = 0;
    while (dfs(s)) {++ans; fill(Vis.begin(),Vis.end(), false);}
    return ans;
  }
};
