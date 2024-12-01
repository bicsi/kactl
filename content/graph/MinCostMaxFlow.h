/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow with potentials technique.
 * If costs can be negative, call SetPi before Compute,
 * but note that negative cost cycles are not allowed.
 * To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis mincostmaxflow
 * Time: O(FE \log E)
 */
#pragma once

using T = int;
const T INF = numeric_limits<T>::max() / 4;
 
struct MFMC {
  struct Edge { int to, rev; T cap, cost, flow; };
  
  int n;
  vector<vector<Edge>> graph;
  vector<int> par; 
  vector<T> dist, pi;
  vector<Edge> es;
  priority_queue<pair<T, int>> pq; 
  
  MFMC(int n) : n(n), graph(n), par(n), dist(n), pi(n) {}
  
  void AddEdge(int a, int b, T cap, T cost, T flow = 0) {
    graph[a].push_back({b, (int)graph[b].size(), cap, cost, flow});
    graph[b].push_back({a, (int)graph[a].size() - 1, 0, -cost, -flow});
  }
  bool relax(int from, const Edge& e) {
    if (dist[from] == INF) return false;
    T now = dist[from] + pi[from] - pi[e.to] + e.cost;
    if (e.flow < e.cap && now < dist[e.to]) 
      return dist[e.to] = now, par[e.to] = e.rev, true;
    return false;
  }
  bool dijkstra(int s, int t) {
    dist.assign(n, INF); par.assign(n, -1);
    dist[s] = 0; pq.emplace(0, s); 
    while (!pq.empty()) {
      auto [d, node] = pq.top(); pq.pop();
      if (dist[node] != -d) continue;
      for (auto& e : graph[node]) 
        if (relax(node, e))
          pq.emplace(-dist[e.to], e.to);
    }
    for (int i = 0; i < n; ++i)
      pi[i] = min(pi[i] + dist[i], INF);
    return par[t] != -1;
  }
  pair<T, T> Compute(int s, int t) {
    T flow = 0, cost = 0;
    while (dijkstra(s, t)) {
      T now = INF;
      for (int phase : {0, 1}) {
        for (int node = t; node != s; ) {
          auto& e1 = graph[node][par[node]];
          auto& e2 = graph[e1.to][e1.rev];
          if (!phase) now = min(now, e2.cap - e2.flow);
          else e2.flow += now, e1.flow -= now;
          node = e1.to;
        }
      }
      flow += now;
      cost += pi[t];
    }
    return {flow, cost};
  }
  // If some costs can be negative, call this before maxflow:
  void SetPi(int s) { // (otherwise, leave this out)
    dist.assign(n, INF); dist[s] = 0;
    int it = n, ch = 1;
    while (ch-- && it--)
      for (int i = 0; i < n; ++i)
        for (auto& e : graph[i])
          ch |= relax(i, e);
    assert(it >= 0); // negative cost cycle
    pi = dist;
  }
};
