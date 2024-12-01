/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: Bunicul
 * Description: A slow, albeit very easy-to-implement
 * flow algorithm. Mutates graph. Prefer this to DinicFlow
 * when constraints allow.
 * Time: O(EF) where $F$ is the maximum flow.
 * Usage: while (PushFlow(graph, 0, n - 1)) ++ans;
 * Status: works
 */
#pragma once

bool PushFlow(vector<vector<int>>& graph, int s, int t) {
  vector<bool> vis(graph.size(), false);
  function<bool(int)> dfs = [&](int node) {
    if (node == t) return true;
    vis[node] = true;
    for (auto& vec : graph[node]) 
      if (!vis[vec] && dfs(vec)) {
        graph[vec].push_back(node);
        swap(vec, graph[node].back());
        graph[node].pop_back();
        return true;
      }
    return false;
  };
  return dfs(s);
}