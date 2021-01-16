/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.Query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#pragma once

struct RMQ {
  vector<vector<T>> rmq;

  void Build(const vector<T>& v) {
    int n = v.size(), depth = 1;
    while ((1 << depth) < n * 2) ++depth;
    rmq.assign(depth, v);
    for (int i = 0; i < depth - 1; ++i)
      for (int j = 0; j + (2 << i) <= n; ++j) 
        rmq[i + 1][j] = min(rmq[i][j], rmq[i][j + (1 << i)]);
  }
  T Query(int a, int b) {
    assert(a < b);
    int dep = 31 - __builtin_clz(b - a); // log(b - a)
    return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
  }
};
