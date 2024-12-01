/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Dijkstra optimization on graphs with small costs.
 * Edges of graph must have costs in the range $[0..lim)$. 
 * Also works for cases where maximum distance is bounded by 
 * something small (just set $lim=maxd+1$).
 * Particularly useful for linear $0-1$ BFS.
 * Time: $O(V + E + maxd)$.
 * Status: Tested adaptation on SPOJ KATHTHI
 */
#pragma once

template<typename Graph>
vector<int> Dijkstra(Graph& graph, int src, int lim) {
  vector<vector<int>> qs(lim);
  vector<int> dist(graph.size(), -1);

  dist[src] = 0; qs[0].push_back(src);
  for (int d = 0, maxd = 0; d <= maxd; ++d) {
    for (auto& q = qs[d % lim]; q.size(); ) {
      int node = q.back(); q.pop_back();
      if (dist[node] != d) continue;
      for (auto [vec, cost] : graph[node]) {
        if (dist[vec] != -1 && dist[vec] <= d + cost) continue;
        dist[vec] = d + cost;
        qs[(d + cost) % lim].push_back(vec);
        maxd = max(maxd, d + cost);
      }
    }
  }
  return dist;
}