/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Disjoint Sparse Table implementation. Returns
 * $\min_{i=l}^{r-1} v[i]$ in constant time. Can be 
 * adapted for other things, like sum or product.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.Query(inclusive, exclusive);
 * Time: $O(N \log N + Q)$
 * Status: stress-tested
 */
#pragma once
 
struct RMQ {
  vector<int> dp[32];
  
  RMQ(const vector<int> &v) {
    int n = v.size();
    for (int h = 0, l = 1; l <= n; ++h, l *= 2) {
      dp[h].resize(n + 1, 1e9);
      for (int m = l; m < n + l; m += 2 * l) {
        for (int i = m + 1; i <= min(n, m + l); i++)
          dp[h][i] = min(dp[h][i - 1], v[i - 1]);
        for (int i = min(n, m) - 1; i >= m - l; i--)
          dp[h][i] = min(v[i], dp[h][i + 1]);
      }
    }
  }
  int Query(int l, int r) {
    int h = 31 - __builtin_clz(l ^ r);
    return min(dp[h][l], dp[h][r]);
  }
};