/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Quick flow algorithm. If it TLEs on ugly inputs,
 * adapt it to use capacity scaling.
 * Time: $O(V^2 E)$ or $O(E \sqrt{E})$ on unit graphs.
 * Status: Tested on kattis, SPOJ FASTFLOW, infoarena maxflow
 */
#pragma once

using T = int;

struct Dinic {
  struct Edge { int from, to, nxt; T cap, flow; };
   
  vector<Edge> es;
  vector<int> graph, at, dist, q;
  
  Dinic(int n) : graph(n, -1) {}
  
  int AddEdge(int a, int b, T c, bool dir = true) {
    auto add = [&](int a, int b, T c) {
      es.push_back({a, b, graph[a], c, 0});
      graph[a] = es.size() - 1;
    };
    add(a, b, c); add(b, a, dir ? 0 : c);
    return es.size() - 2;
  } 
  bool bfs(int src, int dest) {
    dist.assign(graph.size(), -1); q.clear();
    dist[src] = 0; q.push_back(src);
    for (int i = 0; i < (int)q.size(); ++i) {
      int node = q[i];
      for (int ei = graph[node]; ei >= 0; ei = es[ei].nxt) {
        const auto &e = es[ei];
        if (dist[e.to] == -1 && e.cap > e.flow) {
          dist[e.to] = dist[node] + 1;
          q.push_back(e.to);
        }
      }
    }
    return dist[dest] != -1;
  }
  T dfs(int node, int dest, T need) {
    if (!need || node == dest) return need;
    T ret = 0;
    for (int& ei = at[node]; ei != -1; ei = es[ei].nxt) {
      const auto &e = es[ei];
      if (dist[e.to] != dist[node] + 1) continue;
      if (T now = dfs(e.to, dest, min(need, e.cap - e.flow))) {
        es[ ei ].flow += now;
        es[ei^1].flow -= now;
        ret += now; need -= now;
      }
      if (!need) break;
    }
    return ret;
  }
  T Compute(int src, int dest) {
    T ret = 0;
    while (bfs(src, dest)) {
      at = graph;
      ret += dfs(src, dest, numeric_limits<T>::max());
    }
    return ret;
  }
  bool SideOfCut(int x) { return dist[x] == -1; } 
};