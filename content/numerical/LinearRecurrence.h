/**
 * Author: Lucian Bicsi
 * Source: Chinese material
 * Description: Generates the k-th term of a n-th order
 * linear recurrence given the first n terms and the
 * recurrence relation. Faster than matrix multiplication.
 * Useful to use along with Berlekamp Massey.
 * Recurrence is $s_i = \sum_{j=0}^{n-1} s_{i-j-1} * trans_{j}$
 * where $first = \{s_0, s_1, ..., s_{n - 1}\}$
 * Usage: LinearRec({0, 1}, {1, 1}, k) gives k-th
 * Fibonacci number (0-indexed)
 * Time: O(N^{2} log(K)) per query
 */
#pragma once 

using Poly = vector<ModInt>;

ModInt LinearRec(Poly first, Poly trans, int k) {
  int n = trans.size(); // assert(n <= (int)first.size());
  Poly r(n + 1, 0), b(r); r[0] = b[1] = 1;
  auto ans = b[0];

  auto combine = [&](Poly a, Poly b) { // a * b mod trans
    Poly res(n * 2 + 1, 0);
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= n; ++j)
        res[i + j] = res[i + j] + a[i] * b[j];
    for (int i = 2 * n; i > n; --i)
      for (int j = 0; j < n; ++j)
        res[i - 1 - j] = res[i - 1 - j] + res[i] * trans[j];
    res.resize(n + 1);
    return res;
  };
  // Consider caching the powers for multiple queries
  for (++k; k; k /= 2) {
    if (k % 2) r = combine(r, b);
    b = combine(b, b);
  }
  for (int i = 0; i < n; ++i)
    ans = ans + r[i + 1] * first[i];
  return ans;
}
