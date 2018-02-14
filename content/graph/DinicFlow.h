/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Quick flow algorithm.
 * Time: $O(V^2 * E)$ or $O(E * sqrt(E))$ on unit graphs
 * Status: Tested on kattis and SPOJ
 */
#pragma once

struct Dinic {
  struct Edge { int to, cap, flow, nxt; };
  
  vector<Edge> edges;
  vector<int> graph, at, dist;
  int src = 0, dest = 1;
  
  Dinic(int n) : graph(n, -1), dist(n, -1) {}
  
  void add_edge(int from, int to, int cap) {
    edges.push_back(Edge {to, cap, 0, graph[from]});
    graph[from] = edges.size() - 1;
  }
  void AddEdge(int from, int to, int cap) {
    add_edge(from, to, cap);
    add_edge(to, from, 0);
  }
  
  bool bfs() {
    queue<int> q;
    fill(dist.begin(), dist.end(), -1);
    dist[src] = 0; q.push(src);
    
    while (!q.empty()) {
      int node = q.front(); q.pop();
      for (int i = graph[node]; i >= 0; i = edges[i].nxt) {
        const auto &e = edges[i];
        if (dist[e.to] == -1 && e.flow < e.cap) {
          dist[e.to] = dist[node] + 1;
          q.push(e.to);
        }
      }
    }
    
    return dist[dest] != -1;
  }
  
  int dfs(int node, int flow) {
    if (flow == 0) return 0;
    if (node == dest) return flow;
    
    while (at[node] != -1) {
      int eid = at[node]; const auto &e = edges[eid];
      
      if (dist[e.to] == dist[node] + 1) {
        if (int ret = dfs(e.to, min(flow, e.cap - e.flow))) {
          edges[ eid ].flow += ret;
          edges[eid^1].flow -= ret;
          return ret;
        }
      }
      
      at[node] = e.nxt;
    }
    return 0;
  }
  
  int Compute(int src, int dest) {
    this->src = src; this->dest = dest; int ret = 0;
    while (bfs()) {
      at = graph;
      while (int flow = dfs(src, 2e9))
        ret += flow;
    }
    return ret;
  }
};
