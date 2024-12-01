/**
 * Author: Lucian Bicsi
 * Date: 2021-08-23
 * License: CC0
 * Source: folklore
 * Description: Eulerian undirected/directed path/cycle algorithm.
 * For a directed/undirected graph. For each path/cycle found,
 * calls a callback. You can check cycle by checking path endpoints.
 * Time: $O(V + E)$.
 * Status: tested on CSA xor-the-graph
 */
#pragma once

bool DIR = false;

struct EulerWalk {
  int n;
  vector<vector<pair<int, int>>> graph;
  vector<int> cap, walk, buf, deg;
  
  EulerWalk(int n) : n(n), graph(n + 1), deg(n + 1) {}
  
  int AddEdge(int a, int b, int c = 1) {
    int ret = cap.size();
    graph[b].emplace_back(a, ret);
    if (!DIR) graph[a].emplace_back(b, ret);
    cap.push_back(c);
    deg[a] += c; deg[b] -= c;
    if (!DIR) deg[a] %= 2, deg[b] %= 2;
    return ret;
  }
    
  void dfs(int node) {
    while (graph[node].size()) {
      auto [vec, ei] = graph[node].back();
      if (!cap[ei]) graph[node].pop_back();
      else --cap[ei], dfs(vec);
    }
    walk.push_back(node);
  }
  
  template<typename CB>
  void Go(CB&& cb) {
    for (int i = 0; i <= n; ++i) {
      if (deg[i] < 0) Add(i, n, -deg[i]);
      if (deg[i] > 0) Add(n, i, +deg[i]);
      assert(deg[i] == 0);
    }
    for (int i = n; i >= 0; --i) 
      dfs(i), walk.push_back(n); 
    for (int i = 0, j = 0; i < (int)walk.size(); i = j + 1) {
      for (j = i; walk[j] < n; ++j);
      if (j - i > 1) cb({walk.begin() + i, walk.begin() + j});
    }
  }
};