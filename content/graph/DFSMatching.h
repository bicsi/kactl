/**
 * Author: Lukas Polacek
 * Date: 2009-10-28
 * License: CC0
 * Source:
 * Description: This is a simple matching algorithm but should
 * be just fine in most cases. $n$ is the size of the left
 * partition and $m$ is the size of the right partition.
 * If you want to get the matched pairs, $match[i]$ contains
 * match for vertex $i$ on the right side or $-1$ if it's not
 * matched. Performance can be sigmificantly improved by splitting the
 * condition at (*) and/or by randomizing the order at (**).
 * Time: O(EV) where $E$ is the number of edges and V is the number of vertices.
 * Status: works
 */
#pragma once
#include <bits/stdc++.h>

using namespace std;

struct BipartiteMatcher {
  int n, m;
  vector<vector<int>> G;
  vector<int> L, R, vis;
  
  BipartiteMatcher(int n, int m) :
    n(n), m(m), G(n), L(n, -1), R(m, -1), vis(n) {}
  
  void AddEdge(int a, int b) {
    G[a].push_back(b);
  }
  
  bool match(int node) {
    if (vis[node])
      return false;
    vis[node] = true;
    
    for (auto vec : G[node]) {
      if (R[vec] == -1 || match(R[vec])) { // (*)
        L[node] = vec; R[vec] = node; return true;
      }
    }
    return false;
  }

  int Solve() {
    int ok = 1;
    while (ok--) {
      fill(vis.begin(), vis.end(), 0);
      for (int i = 0; i < n; ++i) // (**)
        if (L[i] == -1)
          ok |= match(i);
    }
    return n - count(L.begin(), L.end(), -1);
  }

  // Only include if you want vertex cover
  vector<bool> CL, CR;

  void cover(int node) {
    for (auto vec : G[node]) if (!CR[vec]) {
      CR[vec] = true; 
      CL[R[vec]] = false; 
      cover(R[vec]);
    }
  }

  int VertexCover() {
    int ret = Solve();
    CL.assign(n, false); CR.assign(m, false);
    for (int i = 0; i < n; ++i) if (L[i] != -1) CL[i] = true;
    for (int i = 0; i < n; ++i) if (L[i] == -1) cover(i);
    return ret;
  }
};
