/**
 * Author: chilli, pajenegod
 * Date: 2020-02-20
 * License: CC0
 * Source: Folklore
 * Status: Somewhat tested
 * Description: Lowest common ancestor. Finds the lowest common
 * ancestor in a tree (with 0 as root). C should be an adjacency list of the tree,
 * either directed or undirected.
 * Can also find the distance between two nodes.
 * Usage:
 *  LCA lca(undirGraph);
 *  lca.Query(firstNode, secondNode);
 *  lca.Distance(firstNode, secondNode);
 * Time: $O(|V| \log |V| + Q)$
 */
#pragma once

#include "../data-structures/RMQ.h"

struct LCA {
  vector<int> enter, depth;
  vector<vector<int>> graph;
  vector<pair<int, int>> lin;
  RMQ<pair<int, int>> rmq;
  int timer = 0;

  LCA(int n) : enter(n, -1), depth(n), graph(n), lin(2 * n) {}

  void dfs(int node, int dep) {
    enter[node] = timer; depth[node] = dep;
    lin[timer++] = {dep, node};
    for (auto vec : graph[node])
      if (enter[vec] == -1) {
        dfs(vec, dep + 1);
        lin[timer++] = {dep, node};
      }
  }
  void AddEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  void Build(int root) {
    dfs(root, 0);
    rmq.Build(lin);
  }
  int Query(int a, int b) {
    a = enter[a], b = enter[b];
    return rmq.Query(min(a, b), max(a, b) + 1).second;
  }
  int Distance(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[Query(a, b)];
  }
};