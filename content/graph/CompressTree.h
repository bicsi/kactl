/**
 * Author: Simon Lindholm
 * Date: 2016-01-14
 * License: CC0
 * Status: Tested at CodeForces
 * Description: Given a rooted tree and a subset S of nodes, compute the minimal
 * subtree that contains all the nodes by adding all (at most $|S|-1$)
 * pairwise LCA's and compressing edges.
 * Returns the nodes of the reduced tree, while at the same
 * time populating a link array that stores the new parents.
 * The root points to -1.
 * Time: $O(|S| * (\log |S| + LCA\_Q))$
 */
#pragma once

#include "LCA.h"

vector<int> CompressTree(vector<int> v, LCA& lca,
                         vector<int>& link) {
  auto cmp = [&](int a, int b) {
    return lca.enter[a] < lca.enter[b];
  };
  sort(v.begin(), v.end(), cmp);
  v.erase(unique(v.begin(), v.end()), v.end());
  
  for (int i = (int)v.size() - 1; i > 0; --i)
    v.push_back(lca.Query(v[i - 1], v[i]));
  
  sort(v.begin(), v.end(), cmp);
  v.erase(unique(v.begin(), v.end()), v.end());
  
  for (int i = 0; i < (int)v.size(); ++i)
    link[v[i]] = (i == 0 ? -1 : lca.Query(v[i - 1], v[i]));
  return v;
}
