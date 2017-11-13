/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min-cost max-flow with potentials technique.
 *  If costs can be negative, call SetPi before Compute,
 * but note that negative cost cycles are not allowed (that's NP-hard).
 *  To obtain the actual flow, look at positive values only.
 * Status: Tested on kattis mincostmaxflow
 * Time: Approximately O(E^2). Another upper bound is O(FE \log E)
 */
#include <bits/stdc++.h>
#include <bits/extc++.h>

using namespace std;

using T = int;
const T kInf = numeric_limits<T>::max() / 4;

struct MFMC {
  struct Edge { int to, nxt; T flow, cap, cost; };
  vector<Edge> edges;
  
  int n;
  vector<T> dist, pi;
  vector<int> par, graph;
  
  MFMC(int n) :
  n(n), dist(n), pi(n, 0), par(n), graph(n, -1) {}
  
  void _addEdge(int from, int to, T cap, T cost) {
    edges.push_back(Edge{to, graph[from], 0, cap, cost});
    graph[from] = edges.size() - 1;
  }
  void AddEdge(int from, int to, T cap, T cost) {
    _addEdge(from, to, cap, cost);
    _addEdge(to, from, 0, -cost);
  }
  
  bool dijkstra(int s, int t) {
    fill(dist.begin(), dist.end(), kInf);
    fill(par.begin(), par.end(), -1);
    
    __gnu_pbds::priority_queue<pair<T, int>> q;
    vector<decltype(q)::point_iterator> its(n);
    
    dist[s] = 0; q.push({0, s});
    while (!q.empty()) {
      int node; T d;
      tie(d, node) = q.top(); q.pop();
      if (dist[node] != -d) continue;
      for (int i = graph[node]; i >= 0; ) {
        const auto &e = edges[i];
        T now = dist[node] + pi[node] - pi[e.to] + e.cost;
        if (e.flow < e.cap && now < dist[e.to]) {
          dist[e.to] = now;
          par[e.to] = i;
          if (its[e.to] == q.end())
            its[e.to] = q.push({-dist[e.to], e.to});
          else q.modify(its[e.to], {-dist[e.to], e.to});
        }
        i = e.nxt;
      }
      
    }
    for (int i = 0; i < n; ++i)
    pi[i] = min(pi[i] + dist[i], kInf);
    return par[t] != -1;
  }
  
  pair<T, T> Compute(int s, int t) {
    T flow = 0, cost = 0;
    while (dijkstra(s, t)) {
      T now = kInf;
      for (int node = t; node != s; ) {
        int ei = par[node];
        now = min(now, edges[ei].cap - edges[ei].flow);
        node = edges[ei ^ 1].to;
      }
      for (int node = t; node != s; ) {
        int ei = par[node];
        edges[ei].flow += now;
        edges[ei ^ 1].flow -= now;
        cost += edges[ei].cost * now;
        node = edges[ei ^ 1].to;
      }
      flow += now;
    }
    return {flow, cost};
  }
  
  // If some costs can be negative, call this before maxflow:
  void SetPi(int s) { // (otherwise, leave this out)
    fill(pi.begin(), pi.end(), kInf); pi[s] = 0;
    int it = n, ch = 1; T v;
    while (ch-- && it--)
      for (int i = 0; i < n; ++i) if (pi[i] != kInf)
        for (int ei = graph[i]; ei >= 0; ) {
          const auto& e = edges[ei];
          if (e.cap && (v = pi[i] + e.cost) < pi[e.to])
            pi[e.to] = v, ch = 1;
          ei = e.nxt;
        }
    assert(it >= 0); // negative cost cycle
  }
};
