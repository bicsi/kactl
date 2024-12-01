/**
 * Author: Lucian Bicsi
 * Description: Container where you can add lines of the form 
 * $a \cdot X + b$, and query maximum values at points $x$.
 * Useful for dynamic programming.
 * To change to minimum, either change the sign of all
 * comparisons, or just add lines of form $(-a)\cdot X + (-b)$ 
 * instead and negate the result.
 * Time: O(\log MAX) per operation
 * Status: tested
 */

struct Line { ll a, b; };

struct ConvexTree {
  struct Node { int dp; int l = -1, r = -1; };
  vector<Node> T; vector<Line> L;
  const int MAX = 1e9; // >= abs(x) for all queries.
  int root = -1;
  
  ll eval(int i, int x) { return L[i].a * x + L[i].b; }
  int update(int node, int b, int e, int upd) {
    if (node == -1) {
      T.push_back({upd});
      return T.size() - 1;
    }
    int& cur = T[node].dp;
    int m = (b + e) / 2;
    int l = T[node].l, r = T[node].r;
    bool bb = eval(upd, b) > eval(cur, b);
    bool bm = eval(upd, m) > eval(cur, m);
    if (bm) swap(cur, upd);
    if (e - b == 1) { /* do nothing */ } 
    else if (bb != bm) l = update(l, b, m, upd);
    else r = update(r, m, e, upd);
    T[node].l = l; T[node].r = r;
    return node;
  }
  ll query(int node, int b, int e, int x) {
    if (node == -1) return -INF; // <= a * x + b for all lines.
    int m = (b + e) / 2;
    return max(eval(T[node].dp, x), (x <= m 
      ? query(T[node].l, b, m, x)
      : query(T[node].r, m + 1, e, x)));
  }
  void Update(Line l) { 
    L.push_back(l); 
    root = update(root, -MAX, MAX, L.size() - 1); 
  } 
  ll Query(int x) { return query(root, -MAX, MAX, x); }
};
