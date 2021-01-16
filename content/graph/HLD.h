/**
 * Author: Lucian Bicsi
 * Date: 2020-12-30
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 *  edges such that the path from any leaf to the root contains at most log(n)
 *  light edges.
 */
#pragma once

struct HeavyLight {
  vector<int> jump, sub, depth, enter, parent;
  vector<vector<int>> graph;
  int timer = 0;
  
  HeavyLight(int n) : 
      jump(n), sub(n), depth(n), 
      enter(n), parent(n), graph(n) {}
  
  void AddEdge(int a, int b) {
    graph[a].push_back(b);
    graph[b].push_back(a);
  }
  void Build(int root) {
    dfs1(root, -1, 0); dfs2(root, root);
  }
  // Returns the position in the HL linearization
  int GetPos(int node) {
    assert(timer); // Call Build() before
    return enter[node];
  }
  // Computes an array of ranges of form [li...ri)
  // that correspond to the ranges you would need
  // to query in the underlying structure
  void GetRanges(int a, int b, vector<pair<int, int>>& ret) {
    assert(timer); // Call Build() before
    while (jump[a] != jump[b]) {
      if (depth[jump[a]] < depth[jump[b]]) swap(a, b);
      ret.emplace_back(enter[jump[a]], enter[a] + 1);
      a = parent[jump[a]];
    }
    if (depth[a] < depth[b]) swap(a, b);
    ret.emplace_back(enter[b], enter[a] + 1);
  }
  
  int dfs1(int node, int par, int dep) {
    sub[node] = 1; parent[node] = par; depth[node] = dep;
    if (par != -1) 
      graph[node].erase(
        find(graph[node].begin(), graph[node].end(), par));
    for (auto vec : graph[node])
      sub[node] += dfs1(vec, node, dep + 1);
    return sub[node];
  }
  void dfs2(int node, int jmp) {
    jump[node] = jmp; enter[node] = timer++;
    iter_swap(graph[node].begin(), max_element(
      graph[node].begin(), graph[node].end(), 
        [&](int a, int b) { return sub[a] < sub[b]; }
    ));
    for (auto vec : graph[node])
      dfs2(vec, vec == graph[node].front() ? jmp : vec);
  }
};