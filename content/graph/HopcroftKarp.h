/**
 * Author: Lucian Bicsi
 * Date: 2020-04-10
 * License: CC0
 * Source:
 * Description: Hopcroft-Karp bipartite matching algorithm.
 * Time: $O(E \sqrt{V})$ where $E$ is the number of edges and $V$ 
 * is the number of vertices. 
 * Status: tested on spoj MATCHING, cses School Dance
 */

vector<int> Match(vector<vector<int>>& graph, int n, int m) {
  vector<int> l(n, -1), r(m, n), q, dist;
  function<bool(int)> dfs = [&](int u) {
    if (u == n) return true;
    int d = dist[u]; dist[u] = -1;
    for (auto v : graph[u]) 
      if (dist[r[v]] == d + 1 && dfs(r[v])) 
        return l[u] = v, r[v] = u, true;
    return false;
  };
  while (true) {
    dist.assign(n + 1, -1); q.clear();
    for (int i = 0; i < n; ++i)
      if (l[i] == -1)
        dist[i] = 0, q.push_back(i);
    for (int i = 0; i < (int)q.size(); ++i) {
      int u = q[i]; if (u == n) break;
      for (auto v : graph[u])
        if (dist[r[v]] == -1)
          dist[r[v]] = 1 + dist[q[i]], q.push_back(r[v]);
    }
    if (dist[n] == -1) break;
    for (int i = 0; i < n; ++i) 
      if (l[i] == -1) 
        dfs(i);
  }
  return l;
}