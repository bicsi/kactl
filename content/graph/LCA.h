/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Status: Somewhat tested
 * Description: Lowest common ancestor. Finds the lowest common
 * ancestor in a rooted tree.
 * Usage:
 *  LCA lca(graph);
 *  lc = lca.Query(u, v);
 * Time: $O(N \log N + Q)$
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
  int n, timer = 0;
  vector<int> enter, pv, pt;
  RMQ rmq;

  LCA(vector<vector<int>>& graph, int root = 0) : 
    n(graph.size()), enter(n, -1), 
    rmq((dfs(graph, root), pt)) {}

  void dfs(auto& graph, int node) {
    enter[node] = timer++;
    for (auto vec : graph[node]) {
      if (enter[vec] != -1) continue;
      pv.push_back(node), pt.push_back(enter[node]);
      dfs(graph, vec);
    }
  }
  int Query(int a, int b) {
    if (a == b) return a;
    a = enter[a], b = enter[b]; 
    return pv[rmq.Query(min(a, b), max(a, b))];
  }
  // Distance is depth[a] + depth[b] - 2 depth[Query(a, b)]
};