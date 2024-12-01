/**
 * Author: Lucian Bicsi
 * Date: 2020-12-03
 * License: CC0
 * Source:
 * Description: This is a simple matching algorithm but should
 * be just fine in most cases. Works very fast for all 
 * cases, including non-bipartite graphs. For bipartite graphs,
 * you can safely set rem = 1 ar (*). If getting WA
 * on non-bipartite graphs, increase number of iterations (*) 
 * or use a proper algorithm.
 * Time: $O(EV)$ where $E$ is the number of edges and $V$ 
 * is the number of vertices. 
 * Status: works
 */

mt19937 rng(time(0));

vector<int> Match(vector<vector<int>>& graph) {
  int n = graph.size(), rem = 1;
  vector<int> vis(n), mate(n, -1), order(n);
  auto mateup = [&](int a, int b) {
    int c = mate[b]; mate[a] = b; mate[b] = a;
    if (c != -1) mate[c] = -1;
    return c;
  };
  function<bool(int)> dfs = [&](int node) {
    if (vis[node]) return false;
    vis[node] = true;
    shuffle(graph[node].begin(), graph[node].end(), rng);
    for (auto vec : graph[node]) 
      if (mate[vec] == -1) 
        return mateup(node, vec), true;
    for (auto vec : graph[node]) {
      int old = mateup(node, vec);
      if (dfs(old)) return true;
      mateup(old, vec);
    }
    return false;
  };
  iota(order.begin(), order.end(), 0);
  while (rem--) {
    shuffle(order.begin(), order.end(), rng);
    vis.assign(n, false);
    for (auto i : order)
      if (mate[i] == -1 && dfs(i)) 
        rem = 50; // (*)
  }
  return mate;
}
