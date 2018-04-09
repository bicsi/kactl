/**
 * Author: Lucian Bicsi
 * Date: 2004-02-08
 * License: CC0
 * Description: Solves $M * x = b$. If there are multiple solutions,
 * returns a solution which has all free variables set to 0.
 * To compute rank, count the number of values in pivot.
 * vector which are not -1.
 * For inverse modulo prime powers,
 * repeatedly set $A^{-1} = A^{-1} (2I - AA^{-1})\
 * (\text{mod }p^k)$ where $A^{-1}$ starts as
 * the inverse of A mod p, and k is doubled in each step.
 * Time: O(vars^2 cons)
 * Status: tested
 */
#pragma once

// Transforms a matrix into its row echelon form
// Returns a vector of pivots for each variable
// vars is the number of variables to do echelon for
vector<int> ToRowEchelon(vector<vector<double>> &M, int vars) {
  int n = M.size(), m = M[0].size();
  vector<int> pivots(vars, -1);
  
  int cur = 0;
  for (int var = 0; var < vars; ++var) {
    if (cur >= n) break;
    
    for (int con = cur + 1; con < n; ++con)
      if (sgn(M[con][var]) != 0)
        swap(M[con], M[cur]);
    
    if (sgn(M[cur][var]) != 0) {
      pivots[var] = cur;
      auto aux = M[cur][var];
      
      for (int i = 0; i < m; ++i)
        M[cur][i] = M[cur][i] / aux;
      
      for (int con = 0; con < n; ++con) {
        if (con != cur) {
          auto mul = M[con][var];
          for (int i = 0; i < m; ++i) {
            M[con][i] = M[con][i] - mul * M[cur][i];
          }
        }
      }
      ++cur;
    }
  }
  
  return pivots;
}

// Computes the inverse of a nxn square matrix.
// Returns true if successful
bool Invert(vector<vector<double>> &M) {
  int n = M.size();
  for (int i = 0; i < n; ++i) {
    M[i].resize(2 * n, 0); M[i][n + i] = 1;
  }
  
  auto pivs = ToRowEchelon(M, n);
  for (auto x : pivs) if (x == -1) return false;
  
  for (int i = 0; i < n; ++i)
    M[i].erase(M[i].begin(), M[i].begin() + n);
  return true;
}

// Returns the solution of a system
// Will change matrix
// Throws 5 if inconsistent
vector<double> SolveSystem(vector<vector<double>> &M,
                           vector<double>& b) {
  int vars = M[0].size();
  for (int i = 0; i < (int)M.size(); ++i)
    M[i].push_back(b[i]);
  
  auto pivs = ToRowEchelon(M, vars);
  vector<double> solution(vars);
  for (int i = 0; i < vars; ++i) {
    solution[i] = (pivs[i] == -1) ? 0 : M[pivs[i]][vars];
  }
  
  // Check feasible (optional)
  for (int i = 0; i < (int)M.size(); ++i) {
    double check = 0;
    for (int j = 0; j < vars; ++j)
      check = check + M[i][j] * solution[j];
    if (sgn(check - M[i][vars]) != 0)
      throw 5;
  }
  
  return solution;
}


