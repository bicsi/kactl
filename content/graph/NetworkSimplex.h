/**
 * Author: Lucian Bicsi
 * Date: 2021-08-24
 * Source: https://codeforces.com/blog/entry/94190
 * Description: Compute instances of minimum cost circulations
 * very fast (faster than SSP). Handles negative cycles and node demands. For edge
 * lower bounds, adjust supplies accordingly. To handle supplies, 
 * modify code at (*) to edges with cost $\infty = 1 + \sum_i c_i$ and capacity $sup_i$.
 * Status: Tested on infoarena fmcm, kattis mincostmaxflow, yosupo minimum cost b-flow
 * Time: Expect $O(\text{poly}(E) \cdot V)$ (very fast in practice)
 */
#pragma once
const int INF = 1e9; // greater than sum(e.k), INF * sum(sup) should fit
using ll = int;

struct NetworkSimplex {
  struct Edge { int a, b, c, k, f = 0; };
 
  int n;
  vector<int> pei, nxt;
  vector<ll> dual;
  vector<Edge> E;
  vector<set<int>> tree;
  vector<int> stk;
  
  NetworkSimplex(int n) : 
    n(n), pei(n + 1, -1), nxt(n + 1, -1),
    dual(n + 1, 0), tree(n + 1) {}
  
  int AddEdge(int a, int b, int c, int k) {
    E.push_back({a, b, c, k});
    E.push_back({b, a, 0, -k});
    return E.size() - 2;
  }
  void build(int ei = -1) {
    stk.push_back(ei);
    while (stk.size()) {
      int ei = stk.back(), v = n; stk.pop_back();
      if (ei != -1) {
        dual[E[ei].b] = dual[E[ei].a] + E[ei].k;
        pei[E[ei].b] = (ei ^ 1);
        v = E[ei].b;
      }
      for (auto nei : tree[v]) 
        if (nei != pei[v]) 
          stk.push_back(nei);
    }
  }
  long long Compute() {
    for (int i = 0; i < n; ++i) {
      int ei = AddEdge(n, i, 0, 0);
      tree[n].insert(ei);
      tree[i].insert(ei^1);
    }  
    build();
 
    long long answer = 0;
    ll flow, cost; int ein, eout, ptr = 0;
    const int B = n / 2 + 1;
    for (int it = 0; it < E.size() / B + 1; ++it) { 
      // Find negative cycle (round-robin). 
      cost = 0; ein = -1;
      for (int t = 0; t < B; ++t, (++ptr) %= E.size()) {
        auto& e = E[ptr];
        ll now = dual[e.a] + e.k - dual[e.b];
        if (e.f < e.c && now < cost)
          cost = now, ein = ptr;
      }
      if (ein == -1) continue;

      // Pivot around ein.
      for (int v = E[ein].b; v < n; v = E[pei[v]].b)
        nxt[v] = pei[v];
      for (int v = E[ein].a; v < n; v = E[pei[v]].b)
        nxt[E[pei[v]].b] = (pei[v]^1);
      nxt[E[ein].a] = -1;
      
      int flow = E[ein].c - E[ein].f; eout = ein;
      for (int ei = ein; ei != -1; ei = nxt[E[ei].b]) {
        int res = E[ei].c - E[ei].f;
        if (res < flow) flow = res, eout = ei;
      }
      for (int ei = ein; ei != -1; ei = nxt[E[ei].b]) 
        E[ei].f += flow, E[ei^1].f -= flow;
      
      if (ein != eout) {
        tree[E[ein].a].insert(ein);
        tree[E[ein].b].insert(ein^1);
        tree[E[eout].a].erase(eout);
        tree[E[eout].b].erase(eout^1);
        build(pei[E[eout].a] == eout ? ein : ein^1);
      }
      answer += 1LL * flow * cost;
      it = -1;
    }
    return answer;
  }
};