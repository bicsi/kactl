/**
 * Author: Emil Lenngren, Simon Lindholm
 * Date: 2011-11-29
 * Source:
 * Description: Calculates a valid assignment to boolean variables a, b, c,... to a 2-SAT problem, so that an expression of the type $(a \vee b) \wedge (!a \vee c) \wedge (d \vee !b) \wedge ...$ becomes true, or reports that it is unsatisfiable.
 * THROWS 5 IF NO SOLUTION
 * Negated variables are represented by bit-inversions (\texttt{\tilde{}x}).
 * Usage:
 *  TwoSat sat(4); // number of variables
 *  sat.Either(0, \tilde3); // Var 0 is true or var 3 is false
 *  sat.SetValue(2); // Var 2 is true
 *  sat.AtMostOne({0,\tilde1,2}); // <= 1 of vars 0, \tilde1 and 2 are true
 *  sat.Solve(); // Returns solution or throws
 * Time: O(N+E), where N is the number of boolean variables, and E is the number of clauses.
 */
#pragma once

struct TwoSat {
  int n;
  vector<vector<int>> G;
  vector<int> values; // 0 = false, 1 = true
  
  TwoSat(int n = 0) : n(n), G(2*n) {}
  
  int AddVar() { // (optional)
    G.emplace_back();
    G.emplace_back();
    return n++;
  }
  
  void Implies(int a, int b) {
    a = (a >= 0 ? 2*a : -1-2*a);
    b = (b >= 0 ? 2*b : -1-2*b);
    G[a].push_back(b);
  }
  void Either(int a, int b) {
    Implies(~a, b);
    Implies(~b, a);
  }
  void SetValue(int x) {
    Either(x, x);
  }
  void AtMostOne(const vector<int>& vals) { // (optional)
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
  
  vector<int> enter, comp, stk;
  int timer = 0;
  int dfs(int node) {
    int low = enter[node] = ++timer, x;
    stk.push_back(node);
    
    for (auto vec : G[node]) if (!comp[vec])
      low = min(low, enter[vec] ?: dfs(vec));
    ++timer;
    if (low == enter[node]) do {
      x = stk.back(); stk.pop_back();
      comp[x] = timer;
      if (values[x >> 1] == -1)
      values[x >> 1] = 1 - x & 1;
    } while (x != node);
    return enter[node] = low;
  }
  
  vector<int> Solve() {
    values.assign(n, -1);
    enter.assign(2 * n, 0); comp = enter;
    for (int i = 0; i < 2 * n; ++i) {
      if (!comp[i])
        dfs(i);
    }
    for (int i = 0; i < n; ++i) {
      if (comp[2 * i] == comp[2 * i + 1])
        throw 5;
    }
    return values;
  }
};
