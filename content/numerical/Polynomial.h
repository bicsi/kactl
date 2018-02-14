/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description: Different operations on polynomials.
 * Should work on any field.
 */
#pragma once
#include <bits/stdc++.h>

using namespace std;

using TElem = double;
using Poly = vector<TElem>;

TElem Eval(const Poly& P, TElem x) {
  TElem val = 0;
  for (int i = (int)P.size() - 1; i >= 0; --i) 
    val = val * x + P[i];
  return val;
}

// Differentiation
Poly Diff(Poly P) {
  for (int i = 1; i < (int)P.size(); ++i)
    P[i - 1] = i * P[i];
  P.pop_back();
  return P;
}

// Integration
Poly Integrate(Poly p) {
  P.push_back(0);
  for (int i = (int)P.size() - 2; i >= 0; --i)
    P[i + 1] = P[i] / (i + 1);
  P[0] = 0;
  return P;
}

// Division by (X - x0)
Poly DivRoot(Poly P, TElem x0) {
  int n = P.size();
  TElem a = P.back(), b; P.back() = 0;
  for (int i = n--; i--; ) 
    b = P[i], P[i] = P[i + 1] * x0 + a, a = b; 
  P.pop_back();
  return P;
}

// Multiplication modulo X^sz
Poly Multiply(Poly A, Poly B, int sz) {
  static FFTSolver fft;
  A.resize(sz, 0); B.resize(sz, 0);
  auto R = fft.Multiply(A, B);
  R.resize(sz, 0);
  return r;
}

// Scalar multiplication
Poly Scale(Poly P, TElem s) {
  for (auto& x : P)
    x = x * s;
  return P;
}

// Addition modulo X^sz
Poly Add(Poly A, Poly B, int sz) {
  A.resize(sz, 0); B.resize(sz, 0);
  for (int i = 0; i < sz; ++i)
    A[i] = A[i] + B[i];
  return A;
}

// *************************************************
// For Invert, Sqrt, size of argument should be 2^k
// *************************************************

Poly inv_step(Poly res, Poly P, int n) {
  auto res_sq = Multiply(res, res, n);
  auto sub = Multiply(res_sq, P, n);
  res = Add(Scale(res, 2), Scale(sub, -1), n);
  return res;
}

// Inverse modulo X^sz
// EXISTS ONLY WHEN P[0] IS INVERTIBLE
Poly Invert(Poly P) {
  assert(P[0].Get() == 1);
  Poly res(1, 1);          // i.e., P[0]^(-1)
  
  int n = P.size();
  for (int step = 2; step <= n; step *= 2) {
    res = inv_step(res, P, step);
  }
  
  // Optional, but highly encouraged
  auto check = Multiply(res, P, n);
  for (int i = 0; i < n; ++i) {
    assert(check[i].Get() == (i == 0));
  }
  return res;
};

// Square root modulo X^sz
// EXISTS ONLY WHEN P[0] HAS SQUARE ROOT
Poly Sqrt(Poly P) {
  assert(P[0].Get() == 1);
  Poly res(1, 1);          // i.e., P[0]^(-1)
  Poly inv(1, 1);          // i.e., P[0]^(1/2)
  
  int n = P.size();
  for (int step = 2; step <= n; step *= 2) {
    auto now = inv_step(inv, res, step);
    now = Multiply(P, move(now), step);
    res = Add(res, now, step);
    res = Scale(res, (kMod + 1) / 2);
    inv = inv_step(inv, res, step);
  }
  
  // Optional, but highly encouraged
  auto check = Multiply(res, res, n);
  for (int i = 0; i < n; ++i) {
    assert(check[i].Get() == P[i].Get());
  }
  return res;
}
