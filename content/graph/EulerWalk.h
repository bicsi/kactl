/**
 * Author: Lucian Bicsi
 * Date: 2009-04-14
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * For a directed / undirected graph. For each path/cycle found,
 * calls a callback. You can check cycle by checking path endpoints.
 * To transform into undirected, toggle comment on lines (*)
 * Time: O(E) where E is the number of edges.
 * Status: tested
 */
#pragma once

struct EulerWalk {
  int n;
  vector<multiset<int>> G;
  vector<int> deg;
  
  EulerWalk(int n) : n(n), G(n + 1), deg(n + 1, 0) {}
  
  void AddEdge(int a, int b) {
    G[b].insert(a);
    deg[a] += 1; deg[b] -= 1;
    // G[a].insert(b); (*)
  }
  
  vector<int> walk;
  void dfs(int node) {
    while (G[node].size()) {
      auto vec = *G[node].begin();
      G[node].erase(G[node].begin());
      // G[vec].erase(G[vec].find(node)); (*)
      dfs(vec);
    }
    walk.push_back(node);
  }
  
  template<typename Callback>
  void Solve(Callback cb) {
    for (int i = 1; i <= n; ++i) {
      while (deg[i] < 0) AddEdge(i, n); // (*)
      while (deg[i] > 0) AddEdge(n, i); // (*)
      // if (deg[i] % 2) AddEdge(i, n); (*)
    }
    // Paths
    vector<int> buff; dfs(n);
    for (auto node : walk) {
      if (node < n) buff.push_back(node);
      else if (buff.size()) {
        cb(buff); buff.clear();
      }
    }
    // Cycles
    for (int i = 0; i < n; ++i) {
      walk.clear(); dfs(i);
      if (walk.size() > 1) cb(walk);
    }
  }
};
