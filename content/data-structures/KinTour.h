/**
 * Author: Lucian Bicsi
 * Description: Kinetic tournament data structure. Allows
 * updates of type modify function $f_i(\cdot)$ and query maximum
 * of $f_i(t)$. Queries have to be increasing in $t$. Modify
 * at will. Useful for temporal sweeps.
 * Time: Approx O(\log^2{N}) amortized per operation.
 * Status: tested on infoarena euro
 */

#pragma once

struct Line { ll a, b; };

struct KinTour {
  struct Node { int dp = 0; ll ev = INF; };
  
  int n; ll t = -INF;
  vector<Node> T; vector<Line> L;
 
  KinTour(int n) : n(n), T(2 * n), L(n, Line{0, 0}) {}
 
  ll eval(int i) { return L[i].a * t + L[i].b; }
  ll div(ll a, ll b) { return a / b - (a % b < 0); }
  ll beats(int i, int j) {
    // we know i beats j at t; when will j beat i after t?
    if (L[i].a >= L[j].a) return INF;
    return 1 + div(L[i].b - L[j].b, L[j].a - L[i].a);
  }
  void go(int x, int b, int e, int pos) {
    if ((e <= pos || b > pos) && T[x].ev > t) return;
    if (e - b == 1) { T[x].dp = b; return; }
    int m = (b + e) / 2, z = x + 2 * (m - b);
    go(x + 1, b, m, pos); go(z, m, e, pos);
    int i = T[x + 1].dp, j = T[z].dp;
    if (eval(i) < eval(j)) swap(i, j);
    T[x] = {i, min({T[x + 1].ev, T[z].ev, beats(i, j)})};
    assert(T[x].ev > t);
  }
  ll EvalMax(ll tt) {
    assert(t <= tt); t = tt; 
    go(1, 0, n, -1);
    return eval(T[1].dp);
  }
  void Update(int i, Line l) { 
    L[i] = l; go(1, 0, n, i); 
  }
};