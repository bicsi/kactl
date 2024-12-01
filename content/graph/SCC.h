/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Usage: SCC(graph, [\&](auto\& v) { ... }) visits all components
 * in reverse topological order. 
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 */
#pragma once

template<class CB>
void SCC(vector<vector<int>>& graph, CB cb) {
  int n = graph.size(), timer = 0;
  vector<int> val(n, 0), stk, cont;
  
  function<int(int)> dfs = [&](int node) {
    int low; low = val[node] = ++timer; 
    int sz = stk.size(); stk.push_back(node);
    for (auto vec : graph[node]) 
        if (val[vec] != -1)
          low = min(low, val[vec] ?: dfs(vec));
    if (low == val[node]) {
      cont = {stk.begin() + sz, stk.end()};
      for (auto x : cont) val[x] = -1;
      cb(cont); stk.resize(sz);
    } else val[node] = low;
    return low;
  };
  for (int i = 0; i < n; ++i) 
    if (val[i] != -1) 
      dfs(i);
}
