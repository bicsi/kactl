/**
 * Author: Lucian Bicsi
 * Date: 2021-08-30
 * License: CC0
 * Status: Tested on MW Fall 2020, https://codeforces.com/contest/1556/problem/H
 * Description: Weighted Matroid intersection algorithm.
 * Given two matroids $M1$ and $M2$ on the same set $[0..n)$,
 * computes the maximal independent set on both matroids. Matroids are functions
 * which should return vector of elements that can be added to an existing solution.
 * For unweighted version, set $w[i] = 0$.
 * Usage:
 *  Color C(colors); Forest F(n, edges);
 *  auto sol = MatroidIntersection(C, F, w);
 * Time: Generally $O(M^2 N)$, where $M$ is the solution size.
 */
#pragma once

template <class M1, class M2>
vector<bool> MatrInter(M1 m1, M2 m2, vector<int> w) {
  int n = w.size();
  vector<bool> sol(n, false);
  while (true) {
    // Build graph.
    vector<vector<int>> graph(n);
    for (int i = 0; i < n; ++i) {
      if (!sol[i]) continue;
      sol[i] = 0;
      for (auto j : m1(sol)) graph[i].push_back(j);
      for (auto j : m2(sol)) graph[j].push_back(i);
      sol[i] = 1;
    }
    // Find augmenting path (Bellman-Ford).
    vector<int> inq(n, 0), parent(n, -2), q;
    vector<long long> dist(n, 1LL * M * M);
    auto push = [&](int v, int p, long long d) {
      if (dist[v] <= d) return;
      dist[v] = d; parent[v] = p;
      if (!inq[v]) inq[v] = 1, q.push_back(v);
    };
    for (auto node : m1(sol))
      push(node, -1, 1LL * w[node] * M);
    for (int i = 0; i < (int)q.size(); ++i) {
      int node = q[i]; inq[node] = 0;
      for (auto vec : graph[node])
        if (vec != node)
          push(vec, node, dist[node] +
              (sol[vec] ? -1LL : 1LL) * w[vec] * n + 1);
    }
    int choose = -1; long long best = 4e18;
    for (auto node : m2(sol))
      if (dist[node] < best)
        best = dist[node], choose = node;
    if (choose == -1) break;
    // Augment.
    for (int node = choose; node != -1; node = parent[node])
      sol[node] = !sol[node];
  }
  return sol;
}
