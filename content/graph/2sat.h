/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * Source:
 * Description: Calculates a valid assignment to boolean variables a, b, c,... 
 * to a 2-SAT problem, so that an expression of the type 
 * $(a \vee b) \wedge (!a \vee c) \wedge (d \vee !b) \wedge ...$ becomes true, 
 * or reports that it is unsatisfiable. Returns empty vector if no solution.
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat sat(4); // number of variables
 *  sat.Either(0, \tilde3); // Var 0 is true or var 3 is false
 *  sat.SetValue(2); // Var 2 is true
 *  sat.AtMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  sat.Solve(); // Returns solution
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 * Status: stress-tested
 */
#pragma once

#include <../data-structures/BiVec.h>

struct TwoSat {
  int n;
  BiVec<vector<int>> graph;
  
  TwoSat(int n) : n(n), graph(n) {}
  
  void Implies(int a, int b) {
    graph[a].push_back(b);
    graph[~b].push_back(~a);
  }
  void Either(int a, int b) { Implies(~a, b); }
  void SetValue(int x) { Either(x, x); }
  int AddVar() { graph.resize(++n); return n - 1; } 
  void AtMostOne(const vector<int>& vals) {
    if (vals.size() <= 1) return;
    int cur = ~vals[0];
    for (int i = 2; i < (int)vals.size(); ++i) {
      int nxt = AddVar();
      Either(cur, ~vals[i]);
      Either(cur, nxt);
      Either(~vals[i], nxt);
      cur = ~nxt;
    }
    Either(cur, ~vals[1]);
  }
  vector<int> Solve() {
    BiVec<int> vis(n); vector<int> stk, ans(n); 
    int cc = 0;

    function<void(int)> dfs1 = [&](int node) {
      if (vis[node]) return;
      vis[node] = -1; 
      for (auto vec : graph[node]) 
        dfs1(vec);
      stk.push_back(node);
    };
    function<void(int)> dfs2 = [&](int node) {
      if (vis[node] != -1) return;
      vis[node] = cc;
      for (auto vec : graph[~node]) 
        dfs2(~vec);
    };
    for (int i = 0; i < n; ++i) dfs1(i), dfs1(~i);
    for (int i = 2 * n - 1; i >= 0; --i) ++cc, dfs2(stk[i]);
    
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
      if (vis[i] == vis[~i]) return {};
      ans[i] = vis[i] > vis[~i];
    }
    return ans;
  }
};
