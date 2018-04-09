/**
 * Author: Simon Lindholm
 * Date: 2017-05-11
 * License: CC0
 * Source: folklore
 * Description: Computes sums a[i,j] for all i<I, j<J, and increases single elements a[i,j].
 *  Requires that the elements to be updated are known in advance (call FakeUpdate() before Init()).
 * Time: $O(\log^2 N)$. (Use persistent segment trees for $O(\log N)$.)
 */
#pragma once

#include "FenwickTree.h"

struct Fenwick2D {
	vector<vector<int>> ys;
  vector<vector<int>> T;
	Fenwick2D(int n) : ys(n + 1) {}
  
	void FakeUpdate(int x, int y) {
    for (++x; x < (int)ys.size(); x += (x & -x))
      ys[x].push_back(y);
	}
	void Init() {
    for (auto& v : ys) {
      sort(v.begin(), v.end());
      T.emplace_back(v.size());
    }
	}
	int ind(int x, int y) {
    auto it = lower_bound(ys[x].begin(), ys[x].end(), y);
    return distance(ys[x].begin(), it);
  }
	void Update(int x, int y, int val) {
		for (++x; x < (int)ys.size(); x += (x & -x))
    for (int i = ind(x,y); i < (int)T[x].size(); i += (i & -i))
      trees[x][i] = trees[x][i] + val;
	}
	int Query(int x, int y) {
		int sum = 0;
		for (; x > 0; x -= (x & -x))
    for (int i = ind(x,y); i > 0; i -= (i & -i))
      sum = sum + T[x][i];
		return sum;
	}
};
