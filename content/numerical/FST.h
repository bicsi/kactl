/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Transform to a basis with fast convolutions of the form
 * $\displaystyle c[x \oplus y] \mathrel{{+}{=}} a[x] \cdot b[y]$,
 * where $\oplus$ is one of AND, OR, XOR. The size of $a$ must be a power of two.
 * Time: O(N \log N)
 * Status: stress-tested
 */
#pragma once

void DFT(vector<int>& a, bool rev) {
  int n = a.size(); // assert(!(n & (n - 1)));
  for (int step = 1; step < n; step *= 2) 
  for (int i = 0; i < n; i += 2 * step) 
  for (int j = i; j < i + step; ++j) {
    auto u = a[j], v = a[j + step];
    tie(a[j], a[j + step]) =
      rev ? make_pair(v - u, u) : make_pair(v, u + v); // AND
      rev ? make_pair(v, u - v) : make_pair(u + v, u); // OR
      make_pair(u + v, u - v);                         // XOR
  }
  if (rev) for (auto& x : a) x /= n; // XOR only 
}
