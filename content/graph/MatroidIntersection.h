/**
 * Author: Lucian Bicsi
 * Date: 2020-11-30
 * License: CC0
 * Status: Tested on MW Fall 2020
 * Description: Matroid intersection algorithm. Given two 
 * matroids $M1$ and $M2$ on the same set $[0..n)$, computes
 * the maximal independent set on both matroids. For weighted
 * matroid intersection, replace BFS with Bellman-Ford to 
 * compute path with minimum $(distance, numEdges)$ (consider 
 * edge $(i, j)$ to have weight $w_j - w_i$).
 * Usage:
 *  Color C(colors); Forest F(n, edges);
 *  auto sol = MatroidIntersection(m, C, F);
 * Time: Generally $O(M^2 N)$, where $M$ is the solution size.
 */
#pragma once

template <class M1, class M2>
vector<bool> MatroidIntersection(int n, M1 m1, M2 m2) {
  vector<bool> sol(n, false);
  int ok = 1;
  while (ok--) {
    auto adm1 = m1.Admits(sol), adm2 = m2.Admits(sol);
    auto ex1 = m1.Exchange(sol), ex2 = m2.Exchange(sol);

    vector<int> parent(n, -2), q;
    for (int i = 0; i < n; ++i) 
      if (!sol[i] && adm1[i])
        parent[i] = -1, q.push_back(i);

    for (int i = 0; i < (int)q.size(); ++i) {
      int node = q[i];
      if (!sol[node] && adm2[node]) {
        for (; node != -1; node = parent[node])
          sol[node] = !sol[node];
        ok = 1; break;
      }
      for (int vec = 0; vec < n; ++vec) 
        if (parent[vec] == -2 && sol[node] != sol[vec]
            && (sol[node] ? ex1[node][vec] : ex2[vec][node]))
          parent[vec] = node, q.push_back(vec);
    }
  }
  return sol;
}