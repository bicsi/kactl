/**
 * Author: Unknown
 * Date: 2014-11-27
 * Source: somewhere on github
 * Description: Calculates determinant using modular arithmetics.
 * Modulos can also be removed to get a pure-integer version.
 * Status: bruteforce-tested for N <= 3, mod <= 7
 * Time: $O(N^3)$
 */
#pragma once

using int64 = int64_t;
const int64 kMod = 12345;

int64 IntDeterminant(vector<vector<int64>>& M) {
  int n = M.size(); int64 ans = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      while (M[j][i] != 0) { // gcd step
        int64 t = M[i][i] / M[j][i];
        if (t) for (int k = i; k < n; ++k)
          M[i][k] = (M[i][k] - M[j][k] * t) % kMod;
        swap(M[i], M[j]);
        ans *= -1;
      }
    }
    ans = ans * a[i][i] % mod;
    if (!ans) return 0;
  }
  return (ans + kMod) % kMod;
}
