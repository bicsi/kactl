/**
 * Author: Lucian Bicsi
 * Date: 2020-02-06
 * License: CC0
 * Source: own work
 * Description: Computes the faces of a planar
 * graph. Returns a permutation $nxt$ where $nxt[i]$ is the next
 * edge in the same face as edge $i$. Faces are trigonometric ordered.
 * It doesn't compute a DCEL per se, but any other information
 * can be recovered (origin is $E[i][0]$, $prv$ can be derived from $nxt$,
 * twin is $i ^\wedge 1$). To make it a little faster, short-circuit the
 * tuple comparison at (*). 
 * Time: O(M \log M)
 * Status: tested on infoarena nowhere-zero
 * Warning: $E$ has to contain both an edge and its reverse;
 * moreover, the reverse of edge $i$ has to be $i ^\wedge 1$.
 */

#pragma once 

vector<int> DCEL(vector<Point>& P, vector<array<int, 2>>& E) {
  int n = P.size(), m = E.size();
  vector<int> ord(m);
  iota(ord.begin(), ord.end(), 0);
  stable_sort(ord.begin(), ord.end(), [&](int a, int b) {
    Point p = P[E[a][1]] - P[E[a][0]], 
          q = P[E[b][1]] - P[E[b][0]];
    return make_tuple(E[a][0], half(p), 0) // (*)
         > make_tuple(E[b][0], half(q), cross(p, q));
  });
  int l = 0, r = 0;
  vector<int> nxt(m);
  for (l = 0; l < m; l = r) {
    for (r = l + 1; r < m && E[ord[r]][0] == E[ord[l]][0]; ++r) 
      nxt[ord[r - 1]] = ord[r];
    nxt[ord[r - 1]] = ord[l];
  }
  for (int i = 0; i < m; i += 2) swap(nxt[i], nxt[i ^ 1]);
  return nxt;
}