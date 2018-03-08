/**
 * Author: Lucian Bicsi
 * Source: Chinese material
 * Description: Generates the k-th term of a n-th order
 * linear recurrence given the first n terms and the
 * recurrence relation. Faster than matrix multiplication.
 * Useful to use along with Berlekamp Massey.
 * Usage: LinearRec<double>({0, 1}, {1, 1}).Get(k) gives k-th
 * Fibonacci number (0-indexed)
 * Time: O(n^{2} log(k)) per query
 * Tested: Somewhat
 */
#include <bits/stdc++.h>

template<typename T>
struct LinearRec {
  using Poly = vector<T>;
  int n; Poly first, trans;
  
  // Recurrence is S[i] = sum(S[i-j-1] * trans[j])
  // with S[0..(n-1)] = first
  LinearRec(const Poly &first, const Poly &trans) :
    n(first.size()), first(first), trans(trans) {}
  
  Poly combine(Poly a, Poly b) {
    Poly res(n * 2 + 1, 0);
    // You can apply constant optimization here to get a
    // ~10x speedup
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= n; ++j)
        res[i + j] = res[i + j] + a[i] * b[j];
    
    for (int i = 2 * n; i > n; --i)
      for (int j = 0; j < n; ++j)
        res[i - 1 - j] = res[i - 1 - j] + res[i] * trans[j];
    
    res.resize(n + 1);
    return res;
  }
  
  // Consider caching the powers for multiple queries
  T Get(int k) {
    Poly r(n + 1, 0), b(r);
    r[0] = 1; b[1] = 1;
    
    for (++k; k; k /= 2) {
      if (k % 2)
        r = combine(r, b);
      b = combine(b, b);
    }
    
    T res = 0;
    for (int i = 0; i < n; ++i)
      res = res + r[i + 1] * first[i];
    return res;
  }
};

