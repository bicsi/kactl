/**
 * Author: 
 * Source: Topcoder
 * Description: Computes Gomory-Hu tree of an undirected graph.
 * Time: O(V) calls of flow algorithm
 * Status: works
 */
#pragma once

tuple<T, int, int> GomoryHu(Dinic& D) {
  int n = D.graph.size(); 
  auto ret = make_tuple(numeric_limits<T>::max(), -1, -1);
  vector<int> par(n, 0); par[0] = -1;
  vector<vector<T>> ans(n, vector<T>(n, get<0>(ret)));

  for (int i = 1; i < n; ++i) {
    T now = D.Compute(i, par[i]);
    for (int j = i + 1; j < n; ++j)
      if (D.SideOfCut(j) == 0 && par[j] == par[i])
        par[j] = i;
    ans[i][par[i]] = ans[par[i]][i] = now;
    for (int j = 0; j < i; ++j)
      ans[i][j] = ans[j][i] = min(now, ans[par[i]][j]);
    ret = min(ret, make_tuple(now, i, par[i]));
    for (auto& e : D.es) e.flow = 0;
  }
  return ret;
}

