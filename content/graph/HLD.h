/**
 * Author: Lucian Bicsi
 * Date: 2020-12-30
 * License: CC0
 * Source: https://codeforces.com/blog/entry/53170, https://github.com/bqi343/USACO/blob/master/Implementations/content/graphs%20(12)/Trees%20(10)/HLD%20(10.3).h
 * Description: Decomposes a tree into vertex disjoint heavy paths and light
 * edges such that the path from any leaf to the root contains at most $log(n)$
 * light edges. If values are on edges, modify (*) to exclude the
 * highest vertex.
 * Warning: Reorders edges of graph. Ranges are inclusive.
 */
#pragma once

struct HeavyLight {
  int n, timer;
  vector<int> jump, sub, depth, enter, parent;
  
  HeavyLight(vector<vector<int>>& graph, int root = 0) :
      n(graph.size()), jump(n), sub(n), 
      depth(n), enter(n), parent(n) {
    for (auto _ : {0, 1}) 
      timer = 0, dfs(graph, root, -1, 0, -1);
  }

  int dfs(auto& graph, int node, int par, int dep, int jmp) {
    if (jmp == -1) jmp = node;
    parent[node] = par; depth[node] = dep; jump[node] = jmp;
    enter[node] = timer++;
    int heavy = 0, ret = 1;
    for (auto& vec : graph[node]) {
      if (vec == par) continue;
      int now = dfs(graph, vec, node, dep + 1, jmp);
      if (heavy < now) heavy = now, swap(vec, graph[node][0]);
      ret += now; jmp = -1;
    }
    return sub[node] = ret;
  }
  // Returns the label in the HL linearization
  int Get(int node) { return enter[node]; }
  // Runs a callback for all ranges [l, r] in the path 
  // a -> b. Some ranges might have l > r; if combining 
  // function is commutative just swap them in callback.
  template<typename Callback>
  void QueryPath(int a, int b, Callback&& cb) {
    if (jump[a] == jump[b]) { 
      cb(enter[a], enter[b]); // (*)
    } else if (depth[jump[a]] > depth[jump[b]]) {
      cb(enter[a], enter[jump[a]]);
      QueryPath(parent[jump[a]], b, cb);
    } else {
      QueryPath(a, parent[jump[b]], cb);
      cb(enter[jump[b]], enter[b]);
    }
  }
  // Range [l, r] corresponding to nodes in the subtree.
  pair<int, int> QuerySubtree(int node) {
    return {enter[node], enter[node] + sub[node] - 1};
  }
};