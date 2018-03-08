/**
 * Author: Lucian Bicsi
 * Description: Container where you can add lines of the form 
 * a * x + b, and query maximum values at points x.
 * Useful for dynamic programming.
 * To change to minimum, either change the sign of all
 * comparisons, the initialization of T and max to min,
 * or just add lines of form (-a)*X + (-b) instead
 * and negate the result.
 * Time: O(\log (kMax - kMin))
 * Status: tested
 */
#include <bits/stdc++.h>

using namespace std;
using int64 = int64_t;

struct Line {
  int a; int64 b;
  int64 Eval(int x) { return 1LL * a * x + b; }
};
const int64 kInf = 2e18; // Maximum abs(A * x + B)
const int kMin = -1e9, kMax = 1e9; // Bounds of query (x)

struct ConvexTree {
  struct Node { int l, r; Line line; };
  vector<Node> T = { Node{0, 0, {0, -kInf}} };
  int root = 0;
  
  int update(int node, int b, int e, Line upd) {
    if (node == 0) {
      T.push_back(Node{0, 0, upd});
      return T.size() - 1;
    }
    
    auto& cur = T[node].line;
    if (cur.Eval(b)>=upd.Eval(b) && cur.Eval(e)>=upd.Eval(e))
      return node;
    if (cur.Eval(b)<=upd.Eval(b) && cur.Eval(e)<=upd.Eval(e))
      return cur = upd, node;
    
    int m = (b + e) / 2;
    if (cur.Eval(b) < upd.Eval(b)) swap(cur, upd);
    if (cur.Eval(m) >= upd.Eval(m)) {
      int res = update(T[node].r, m + 1, e, upd);
      T[node].r = res; // DO NOT ATTEMPT TO OPTIMIZE
    } else {
      swap(cur, upd);
      int res = update(T[node].l, b, m, upd);
      T[node].l = res; // DO NOT ATTEMPT TO OPTIMIZE
    }
    return node;
  }
  void AddLine(Line l) { root = update(root, kMin, kMax, l); }
  
  int64 query(int node, int b, int e, int x) {
    int64 ans = T[node].line.Eval(x);
    if (node == 0) return ans;
    int m = (b + e) / 2;
    if (x <= m) ans = max(ans, query(T[node].l, b, m, x));
    if (x > m) ans = max(ans, query(T[node].r, m + 1, e, x));
    return ans;
  }
  int64 QueryMax(int x) { return query(root, kMin, kMax, x); }
};
