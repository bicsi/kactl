/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Cycle-cancelling algorithm
 * for minimum cost circulation or minimum cost flow
 * (uncomment lines for flow and remove for in iterate)
 * Status: Tested on infoarena
 */
#pragma once

struct CCFlow {
  const int kInf = 1e9;
  struct Edge {
    int to, f, c, k;
    int res() { return c - f; }
  };
  vector<Edge> es;
  vector<vector<int>> G;
  long long cost;
  
  CCFlow(int n) : G(n), in(n), dist(n) {}
  
  void add_edge(int a, int b, int c, int k) {
    G[a].push_back(es.size());
    es.push_back(Edge{b, 0, c, k});
  }
  void AddEdge(int a, int b, int c, int k) {
    add_edge(a, b, c, k);
    add_edge(b, a, 0, -k);
  }
  
  int start, aug;
  vector<int> in;
  vector<long long> dist;
  
  int dfs(int node, int f) {
    if (in[node]) {
      start = node;
      aug = f;
      return 1;
    }
    
    in[node] = true;
    for (auto ei : G[node]) {
      auto& e = es[ei];
      if (dist[e.to] <= dist[node] + e.k or e.res() == 0)
        continue;
      
      dist[e.to] = dist[node] + e.k;
      
      int rec = dfs(e.to, min(f, e.res()));
      if (rec == 2) return 2;
      if (rec == 1) {
        es[ei].f += aug; es[ei ^ 1].f -= aug;
        cost += 1LL * aug * es[ei].k;
        return 1 + (node == start);
      }
    }
    in[node] = false;
    return 0;
  }
  
  bool iterate() {
    bool ok = false;
    for (int s = 0; s < n; ++s) {
      fill(in.begin(), in.end(), 0);
      fill(dist.begin(), dist.end(), 1LL * kInf * kInf);
      dist[s] = 0;
      ok |= dfs(s, kInf);
    }
    return ok;
  }
  long long Solve() {
    // AddEdge(t, s, kInf, -kInf);
    while (iterate());
    // int flow = es[G[t].back()].f;
    // cost += 1LL * flow * kInf;
    return cost;
  }
  
};