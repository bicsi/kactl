/**
 * Author: Simon Lindholm
 * Date: 2016-09-10
 * License: CC0
 * Source: based on KACTL's FFT
 * Description: Number theoretic transform. Can be used for
 * convolutions modulo specific nice primes
 * of the form $2^a b+1$, where the convolution result has size at most $2^a$.
 * For other primes/integers, use two different primes and combine with CRT.
 * If NTT is not fast enough and you are multiplying a lot,
 * consider doing naive solution for the small ones.
 * Time: O(N \log N)
 * Status: Somewhat tested
 */
#pragma once

#include "ModPow.h"

const int kMod = (119 << 23) + 1, kRoot = 3; // = 998244353
// For p < 2^30 there is also e.g. (5 << 25, 3), (7 << 26, 3),
// (479 << 21, 3) and (483 << 21, 5). The last two are > 10^9.

struct FFTSolver {
  vector<int> rev;
  
  int __lg(int n) { return n == 1 ? 0 : 1 + __lg(n / 2);  }
  
  void compute_rev(int n, int lg) {
    rev.resize(n); rev[0] = 0;
    for (int i = 1; i < n; ++i) {
      rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (lg - 1));
    }
  }
  
  vector<ModInt> fft(vector<ModInt> V, bool invert) {
    int n = V.size(), lg = __lg(n);
    if ((int)rev.size() != n) compute_rev(n, lg);
    
    for (int i = 0; i < n; ++i) {
      if (i < rev[i])
        swap(V[i], V[rev[i]]);
    }
    
    for (int step = 2; step <= n; step *= 2) {
      ModInt eps = lgpow(kRoot, (kMod - 1) / step);
      if (invert) eps = inv(eps);
      
      for (int i = 0; i < n; i += step) {
        ModInt w = 1;
        for (int a = i, b = i+step/2; b < i+step; ++a, ++b) {
          ModInt aux = w * V[b];
          V[b] = V[a] - aux;
          V[a] = V[a] + aux;
          w = w * eps;
        }
      }
    }
    
    return V;
  }
  
  vector<ModInt> Multiply(vector<ModInt> A, vector<ModInt> B) {
    int n = A.size() + B.size() - 1, sz = n;
    while (n != (n & -n)) ++n;
    
    A.resize(n, 0); B.resize(n, 0);
    
    A = fft(move(A), false);
    B = fft(move(B), false);
    
    vector<ModInt> ret(n);
    ModInt inv_n = inv(n);
    
    for (int i = 0; i < n; ++i) {
      ret[i] = A[i] * B[i] * inv_n;
    }
    
    ret = fft(move(ret), true);
    ret.resize(sz);
    
    return ret;
  }
};
