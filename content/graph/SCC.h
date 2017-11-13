/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source: Czech graph algorithms book, by Demel. (Tarjan's algorithm)
 * Description: Finds strongly connected components in a
 * directed graph. If vertices $u, v$ belong to the same component,
 * we can reach $u$ from $v$ and vice versa.
 * Time: O(E + V)
 * Status: Bruteforce-tested for N <= 5
 * Usage: SCC(graph, [\&](vi\& v) { ... }) visits all components
 * in reverse topological order. comp[i] holds the component
 * index of a node (a component only has edges to components with
 * lower index). ncomps will contain the number of components.
 */
#pragma once

vector<int> val, comp, stk, cont;
int timer, ncomps;

template<class Graph, class Func>
int dfs(int node, Graph& G, Func f) {
  int low = val[node] = ++timer, x; stk.push_back(node);
  for (auto vec : G[node]) if (comp[vec] < 0)
    low = min(low, val[vec] ?: dfs(vec, G, f));
  
  if (low == val[node]) {
    do {
      x = stk.back(); stk.pop_back();
      comp[x] = ncomps;
      cont.push_back(x);
    } while (x != node);
    f(cont); cont.clear();
    ncomps++;
  }
  return val[node] = low;
}

template<class Graph, class Func>
void SCC(Graph& G, Func f) {
  int n = G.size();
  val.assign(n, 0); comp.assign(n, -1);
  timer = ncomps = 0;
  for (int i = 0; i < n; ++i)
    if (comp[i] < 0)
      dfs(i, G, f);
}
