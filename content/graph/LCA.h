/**
 * Author: Johan Sannemo, Simon Lindholm
 * Date: 2015-09-20
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

const pair<int, int> kInf{1 << 29, -1};

#define RMQ_HAVE_INF /** exclude-line */
#include "../data-structures/RMQ.h"

struct LCA {
  vector<int> enter, depth;
  vector<vector<int>> G;
  vector<pair<int, int>> linear;
  RMQ<pair<int, int>> rmq;
  int timer = 0;
  
  LCA(int n) : enter(n, -1), depth(n), G(n), linear(2 * n) {}
  
  void dfs(int node, int dep) {
    linear[timer] = {dep, node};
    enter[node] = timer++;
    depth[node] = dep;
    
    for (auto vec : G[node])
    if (enter[vec] == -1) {
      dfs(vec, dep + 1);
      linear[timer++] = {dep, node};
    }
  }
  
  void AddEdge(int a, int b) {
    G[a].push_back(b);
    G[b].push_back(a);
  }
  
  void Build(int root) {
    dfs(root, 0);
    rmq.Build(linear);
  }
  
  int Query(int a, int b) {
    a = enter[a], b = enter[b];
    return rmq.Query(min(a, b), max(a, b) + 1).second;
  }
  
  int Distance(int a, int b) {
    return depth[a] + depth[b] - 2 * depth[Query(a, b)];
  }
};
