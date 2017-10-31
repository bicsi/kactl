/**
 * Author: Lucian Bicsi
 * Description: Adds a value to a (half-open) range
 * and computes the sum on a (half-open) range.
 * Beware of overflows!
 * Time: Both operations are $O(\log N)$.
 */
#pragma once

#define int long long
struct FenwickTree {
  int n;
  vector<int> T1, T2;
  
  FenwickTree(int n) : n(n), T1(n + 1, 0), T2(n + 1, 0) {}
  
  void Update(int b, int e, int val) {
    if (e != -1)
      return Update(e, -1, -val), Update(b, -1, +val);
    
    int c1 = val, c2 = val * (b - 1);
    for (int pos = b + 1; pos <= n; pos += (pos & -pos)) {
      T1[pos] += c1; T2[pos] += c2;
    }
  }
  
  int Query(int b, int e) {
    if (b != 0) return Query(0, e) - Query(0, b);
    
    int ans = 0;
    for (int pos = e; pos; pos -= (pos & -pos)) {
      ans += T1[pos] * (e - 1) - T2[pos];
    }
    return ans;
  }
};

