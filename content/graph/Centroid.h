/**
 * Author: Lucian Bicsi
 * Date: 2020-12-29
 * License: CC0
 * Source: Folklore
 * Description: Computes centroid labels and the centroid
 * tree for a given tree. Centroid labels have the property
 * that for any two vertices $u, v$ with $clab[u] = clab[v]$
 * we are guaranteed that there is a vertex $w$ on the path
 * from $u$ to $v$ that has a strictly higher label.
 * In order to simulate tree D\&C, copy the dfs function from 
 * CentrTree and adapt it accordingly. To optimize, convert
 * inline functions to global ones.
 * Time: construction $O(N)$, D\&C $O(N \log N)$
 * Status: Tested on infoarena
 */

vector<int> CentrLabel(vector<vector<int>>& graph) {
  vector<int> clab(graph.size(), -1);
  function<int(int)> dfs = [&](int node) {
    int one = 0, two = 0;
    int& l = clab[node]; l = 0;
    for (auto vec : graph[node]) {
      if (clab[vec] != -1) continue;
      int son = dfs(vec); 
      two |= (one & son); one |= son;
    }
    while (two) ++l, one /= 2, two /= 2;
    while (one % 2) ++l, one /= 2;
    return (one | 1) << l;
  };
  dfs(0); 
  return clab;
}

vector<int> CentrTree(vector<vector<int>>& graph) {
  int n = graph.size(), root;
  vector<int> clab = CentrLabel(graph), cpar(n, -1);
  function<void(int, int)> dfs = [&](int node, int par) {
    for (auto vec : graph[node]) {
      if (vec == par || clab[vec] >= clab[root]) continue;
      if (cpar[vec] == -1 || clab[cpar[vec]] > clab[root])
        cpar[vec] = root;
      dfs(vec, node);
    }
  };
  for (root = 0; root < n; ++root)
    dfs(root, -1);
  return cpar;
}