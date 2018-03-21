/**
 * Author: Stanford
 * Date: Unknown
 * Source: Stanford Notebook
 * Description: Min cost perfect bipartite matching. Negate costs for max cost.
 * Time: O(N^3)
 * Status: tested during ICPC 2015
 */
#pragma once

int sgn(double x) {return abs(x) < 1e-9 ? 0 : x > 0 ? 1 : -1;}
double MinCostMatching(vector<vector<double>> cost, 
    vector<int>& L, vector<int>& R) 
{
  int n = cost.size(), mated = 0;
  vector<double> dist(n), u(n), v(n);
  vector<int> par(n), seen(n);

  /// construct dual feasible solution
  for (int i = 0; i < n; ++i) {
    u[i] = cost[i][0];
    for (int j = 1; j < n; ++j) 
      u[i] = min(u[i], cost[i][j]);
  }
  for (int j = 0; j < n; ++j) {
    v[j] = cost[0][j] - u[0];
    for (int i = 1; i < n; ++i) 
      v[j] = min(v[j], cost[i][j] - u[i]);
  }

  /// find primal solution satisfying complementary slackness
  L = R = vector<int>(n, -1);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j) {
      if (R[j] != -1) continue;
      if (sgn(cost[i][j] - u[i] - v[j]) == 0) {
        L[i] = j; R[j] = i; mated++; break;
      }
    }

  for (; mated < n; mated++) { // until solution is feasible
    int s = 0;
    while (L[s] != -1) s++;

    fill(par.begin(), par.end(), -1);
    fill(seen.begin(), seen.end(), 0);
    for (int k = 0; k < n; ++k)
      dist[k] = cost[s][k] - u[s] - v[k];

    int j = 0;
    while (true) { /// find closest
      j = -1;
      for (int k = 0; k < n; ++k) {
        if (seen[k]) continue;
        if (j == -1 || dist[k] < dist[j]) j = k;
      }
      seen[j] = 1;
      int i = R[j];
      if (i == -1) break;
      for (int k = 0; k < n; ++k) { /// relax neighbors
        if (seen[k]) continue;
        auto new_dist = dist[j] + cost[i][k] - u[i] - v[k];
        if (dist[k] > new_dist) {
          dist[k] = new_dist; 
          par[k] = j;
        }
      }
    }

    /// update dual variables
    for (int k = 0; k < n; ++k) {
      if (k == j || !seen[k]) continue;
      auto w = dist[k] - dist[j];
      v[k] += w, u[R[k]] -= w;
    }
    u[s] += dist[j];

    /// augment along path
    while (par[j] != -1) {
      int p = par[j];
      R[j] = R[p]; L[R[j]] = j; j = p;
    }
    R[j] = s; L[s] = j;
  }
  double ret = 0;
  for (int i = 0; i < n; ++i)
    ret += cost[i][L[i]];
  return ret;
}
