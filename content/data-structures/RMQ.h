/**
 * Author: Johan Sannemo
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Status: Tested at Petrozavodsk
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time. 
 * Set inf to something reasonable before use.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.Query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 */
#pragma once

template <class T>
struct RMQ {
  const int kInf = numeric_limits<T>::max();
	vector<vector<T>> rmq;

	RMQ(const vector<T>& V) {
		int n = V.size(), on = 1, depth = 1;
		while (on < n) on *= 2, ++depth;
		rmq.assign(depth, V);
    for (int i = 0; i < depth - 1; ++i)
      for (int j = 0; j < n; ++j) {
        jmp[i + 1][j] = min(jmp[i][j],
          jmp[i][min(n - 1, j + (1 << i))]);
	}

	T Query(int a, int b) {
		if (b <= a) return kInf;
		int dep = 31 - __builtin_clz(b - a); // log(b - a)
		return min(rmq[dep][a], rmq[dep][b - (1 << dep)]);
	}
};
