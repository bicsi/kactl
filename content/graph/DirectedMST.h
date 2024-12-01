/**
 * Author: ko_osaga, adapted by Lucian Bicsi
 * Date: 2020-12-13
 * License: CC0
 * Source: https://github.com/spaghetti-source/algorithm/blob/master/graph/arborescence.cc
 * and https://github.com/bqi343/USACO/blob/42d177dfb9d6ce350389583cfa71484eb8ae614c/Implementations/content/graphs%20(12)/Advanced/DirectedMST.h for the reconstruction
 * Description: Finds a minimum spanning
 * tree/arborescence of a directed graph, given a root node. 
 * 
 * where $i > 0$.
 * Time: O(M \log N)
 * Status: tested on yosupo judge.
 * Warning: Input graph must be \textbf{strongly connected} and have \textbf{no loops}; 
 * if this is not the case for the problem, consider adding 
 * "fake" edges $(i, 0, \infty)$ and $(0, i, \infty)$.
 */
#pragma once

#include "../data-structures/DSU.h"
#include "../data-structures/SkewHeap.h"

struct Edge { int a, b; ll c; }; 

pair<ll, vector<int>> DMST(int n, int src, vector<Edge> es) {
  // Compress graph - O(M logN)
  SkewHeap H; DSU D(2 * n); int x = 0;
  vector<int> par(2 * n, -1), ins(par), vis(par);
  for (auto e : es) ins[e.b] = H.Merge(ins[e.b], H.New(e.c));
  auto go = [&](int x) { return D.Find(es[ins[x]].a); };
  for (int i = n; ins[x] != -1; ++i) {
    for (; vis[x] == -1; x = go(x)) vis[x] = 0;
    for (; x != i; x = go(x)) {
      int rem = ins[x]; ll w = H.Get(rem); H.Pop(rem);
      H.Add(rem, -w); ins[i] = H.Merge(ins[i], rem);
      par[x] = i; D.link[x] = i;
    }
    for (; ins[x] != -1 && go(x) == x; H.Pop(ins[x]));
  }
  // Expand graph - O(N)
  ll cost = 0; vector<int> ans;
  for (int i = src; i != -1; i = par[i]) vis[i] = 1;
  for (int i = x; i >= 0; --i) {
    if (vis[i]) continue;
    cost += es[ins[i]].c; ans.push_back(ins[i]);
    for (int j = es[ins[i]].b; j != -1 && !vis[j]; j = par[j]) 
      vis[j] = 1;
  }
  return {cost, ans};
}