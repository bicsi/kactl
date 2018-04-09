/**
 * Author: Lucian Bicsi
 * Date: 2015-06-25
 * License: GNU Free Documentation License 1.2
 * Source: csacademy
 * Description: Fast Subset transform. Useful for
 * performing the following convolution:
 * R[a op b] += A[a] * B[b], where op is either of AND, OR, XOR.
 * P has to have size $N = 2^{n}$, for some n.
 * Time: O(N \log N)
 * Status: tested
 */
#pragma once
#include <bits/stdc++.h>

using namespace std;

vector<int> Transform(vector<int> P, bool inv) {
  int n = P.size();
  for (int step = 1; step < n; step *= 2) {
    for (int i = 0; i < n; i += 2 * step) {
      for (int j = i; j < i + step; ++j) {
        int u = P[j], v = P[j + step];
        tie(P[j], P[j + step]) =
        inv ? make_pair(v - u, u) : make_pair(v, u + v); // AND
        inv ? make_pair(v, u - v) : make_pair(u + v, u); // OR
        make_pair(u + v, u - v);                         // XOR
      }
    }
  }
  // if (inv) for (auto& x : P) x /= n; // XOR only
  return P;
}


