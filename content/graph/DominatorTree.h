/**
 * Author: Lucian Bicsi
 * Date: 2020-11-28
 * License: CC0
 * Source: https://tanujkhattar.wordpress.com/2016/01/11/dominator-tree-of-a-directed-graph/
 * Description: Computes the dominator tree $dom$ of a given directed graph $G$.
 * A node $v$ dominates $u$ if all paths from $src$ to $v$ go through $u$.
 * All nodes that aren't reachable from $src$ will have $dom(u) = -1$.
 * $src$ will also have $dom(src) = -1$.
 * Time: $O(M \log N)$ (often faster)
 * Status: tested on MW 2020 Fall
 */
#pragma once

vector<int> DomTree(vector<vector<int>>& graph, int src) {
  int n = graph.size();
  vector<vector<int>> tree(n), trans(n), buck(n);
  vector<int> semi(n), par(n), dom(n), label(n),
    atob(n, -1), btoa(n, -1), link(n, -1);

  function<int(int, int)> find = [&](int u, int d) {
    if (link[u] == -1) 
      return d ? -1 : u;
    int v = find(link[u], d + 1);
    if (v < 0) return u;
    if (semi[label[link[u]]] < semi[label[u]])
      label[u] = label[link[u]];
    link[u] = v;
    return d ? v : label[u];
  };
  int t = 0;
  function<void(int)> dfs = [&](int u) {
    atob[u] = t; btoa[t] = u;
    label[t] = semi[t] = t; t++;
    for (auto v : graph[u]) {
      if (atob[v] == -1)
        dfs(v), par[atob[v]] = atob[u];
      trans[atob[v]].push_back(atob[u]);
    }
  };
  dfs(src);
  for (int u = t - 1; u >= 0; --u) {
    for (auto v : trans[u])
      semi[u] = min(semi[u], semi[find(v, 0)]);
    if (u) buck[semi[u]].push_back(u);
    for (auto w : buck[u]) {
      int v = find(w, 0);
      dom[w] = semi[v] == semi[w] ? semi[w] : v;
    }
    if (u) link[u] = par[u];
  }
  vector<int> ret(n, -1);
  for (int u = 1; u < t; ++u) {
    if (dom[u] != semi[u]) 
      dom[u] = dom[dom[u]];
    ret[btoa[u]] = btoa[dom[u]];
  }
  return ret;
}
