/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Description: Given a rooted tree/forest and a subset $v$ of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|v|-1$)
 * pairwise LCA's and compressing edges.
 * Mutates $v$ to contain nodes of the reduced tree, while at the same
 * time populating a $link$ array that stores the new parents.
 * The root(s) point to -1.
 * Time: $O(|v| * (\log |v| + LCA\_Q))$
 */
#pragma once

#include "LCA.h"

void CompressTree(LCA& L, vector<int>& v, vector<int>& link) {
  for (int it = 0; it < 2; ++it) {
    for (int i = (int)v.size() - 1; i; --i) {
      link[v[i]] = L.Query(v[i - 1], v[i]);
      if (link[v[i]] != -1) v.push_back(link[v[i]]);
    }
    sort(v.begin(), v.end(), [&](int a, int b) {
      return L.enter[a] < L.enter[b];    
    });
    v.erase(unique(v.begin(), v.end()), v.end());
  }
}
