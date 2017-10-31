/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description: Different operations on polynomials.
 * Should work on any field.
 */
#pragma once
#include <bits/stdc++.h>

using namespace std;
using Poly = vector<double>;

double Eval(const Poly& P, double x) {
  double val = 0;
  for (int i = (int)P.size() - 1; i >= 0; --i) 
    val = val * x + P[i];
  return val;
}

Poly Diff(Poly P) {
  for (int i = 1; i < (int)P.size(); ++i)
    P[i - 1] = i * P[i];
  P.pop_back();
  return P;
}

Poly DivRoot(Poly P, double x0) {
  int n = P.size();
  double a = P.back(), b; P.back() = 0;
  for (int i = n--; i--; ) 
    b = P[i], P[i] = P[i + 1] * x0 + a, a = b; 
  P.pop_back();
  return P;
}
