/**
 * Author: Lucian Bicsi
 * Description: Container where you can add lines of the form 
 * a * x + b, and query maximum values at points x.
 * Useful for dynamic programming.
 * Only works with small query values. For large values,
 * reimplement as trie.
 * Time: O(\log N)
 * Status: tested
 */
#include <bits/stdc++.h>
using namespace std;

using int64 = int64_t;

struct Line {
  int64 a, b;
  int64 Eval(int x) { return a * x + b; }
};

struct ConvexTree {
  vector<Line> T;
  int maxx;
  
  ConvexTree(int maxx) :
  T(4 * (maxx+1), Line{0, (int64)-1e18}), maxx(maxx) {}
  
  void Update(int node=1, int b=0, int e=maxx, Line now) {
    Line& cur = T[node];
    if (cur.Eval(b) > now.Eval(b) && cur.Eval(e) > now.Eval(e))
      return;
    if (cur.Eval(b) < now.Eval(b) && cur.Eval(e) < now.Eval(e))
      { cur = now; return; }
    
    int m = (b + e) / 2;
    if (cur.Eval(b) < now.Eval(b)) swap(cur, now);
    if (cur.Eval(m) > now.Eval(m))
      Update(node * 2 + 1, m + 1, e, now);
    else {
      swap(cur, now);
      Update(node * 2, b, m, now);
    }
  }
  
  int64 EvalMax(int node=1, int b=0, int e=maxx, int x) {
    if (b == e) return T[node].Eval(x);
    int m = (b + e) / 2;
    int64 ans = T[node].Eval(x);
    if (x <= m) ans = max(ans, EvalMax(node * 2, b, m, x));
    else ans = max(ans, EvalMax(node * 2 + 1, m + 1, e, x));
    return ans;
  }
};
