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
#include <bits/stdc++.h>

using namespace std;

using T = int;
const T INF = numeric_limits<T>::max() / 4;
 
struct MFMC {
  struct Edge { int from, to, nxt; T flow, cap, cost; };
  
  int n;
  vector<int> graph, par; 
  vector<T> dist, pi;
  vector<Edge> es;
  
  MFMC(int n) : n(n), graph(n, -1), par(n), dist(n), pi(n) {}
  
  void AddEdge(int a, int b, T cap, T cost) {
    auto add = [&](int a, int b, T cap, T cost) {
      es.push_back({a, b, graph[a], 0, cap, cost});
      graph[a] = es.size() - 1;
    };
    add(a, b, cap, cost); add(b, a, 0, -cost);
  }
  bool relax(int ei) {
    const auto &e = es[ei];
    if (dist[e.from] == INF) return false;
    T now = dist[e.from] + pi[e.from] - pi[e.to] + e.cost;
    if (e.flow < e.cap && now < dist[e.to]) 
      return dist[e.to] = now, par[e.to] = ei, true;
    return false;
  }
  bool dijkstra(int s, int t) {
    dist.assign(n, INF); par.assign(n, -1);
    priority_queue<pair<T, int>> pq; 
    dist[s] = 0; pq.emplace(0, s); 
    while (!pq.empty()) {
      auto [d, node] = pq.top(); pq.pop();
      if (dist[node] != -d) continue;
      for (int ei = graph[node]; ei != -1; ei = es[ei].nxt) 
        if (relax(ei)) 
          pq.emplace(-dist[es[ei].to], es[ei].to);
    }
    for (int i = 0; i < n; ++i)
      pi[i] = min(pi[i] + dist[i], INF);
    return par[t] != -1;
  }
  pair<T, T> Compute(int s, int t) {
    T flow = 0, cost = 0;
    while (dijkstra(s, t)) {
      T now = INF;
      for (int ei = par[t]; ei != -1; ei = par[es[ei].from]) 
        now = min(now, es[ei].cap - es[ei].flow);
      for (int ei = par[t]; ei != -1; ei = par[es[ei].from]) {
        es[ ei ].flow += now;
        es[ei^1].flow -= now;
        cost += es[ei].cost * now;
      }
      flow += now;
    }
    return {flow, cost};
  }
  // If some costs can be negative, call this before maxflow:
  void SetPi(int s) { // (otherwise, leave this out)
    dist.assign(n, INF); dist[s] = 0;
    int it = n, ch = 1;
    while (ch-- && it--)
      for (int ei = 0; ei < (int)es.size(); ++ei) 
        ch |= relax(ei);
    assert(it >= 0); // negative cost cycle
    pi = dist;
  }
};