/**
 * Author: Lucian Bicsi
 * Date: 2020-11-27
 * License: CC0
 * Source: Folklore
 * Description: Calculate skew-binary links.
 * Time: construction $O(N)$, queries $O(\log N)$
 * Status: Tested on infoarena
 */
#pragma once

struct Lift {
  struct Data { int par, link, dep; };
  vector<Data> T;

  Lift(int n) : T(n) {}
  
  void Add(int node, int par) {
    if (par == -1) T[node] = Data{-1, node, 0};
    else {
      int link = par, a1 = T[par].link, a2 = T[a1].link;
      if (2 * T[a1].dep == T[a2].dep + T[par].dep)
        link = a2;
      T[node] = Data{par, link, T[par].dep + 1};
    }
  }
  
  int Kth(int node, int k) {
    int seek = T[node].dep - k;
    if (seek < 0) return -1;
    while (T[node].dep > seek) 
      node = (T[T[node].link].dep >= seek) 
        ? T[node].link : T[node].par;
    return node;
  }
  
  int LCA(int a, int b) {
    if (T[a].dep < T[b].dep) swap(a, b);
    while (T[a].dep > T[b].dep) 
      a = (T[T[a].link].dep >= T[b].dep) 
        ? T[a].link : T[a].par;
    while (a != b) {
      if (T[a].dep == 0) return -1;
      if (T[a].link != T[b].link) 
        a = T[a].link, b = T[b].link;
      else a = T[a].par, b = T[b].par;
    }
    return a;
  }
};