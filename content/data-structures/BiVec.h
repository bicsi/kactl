/**
 * Author: Lucian Bicsi
 * Date: 2020-12-26
 * License: CC0
 * Source: own work
 * Description: Bi-directional vector (indices in $[-n..n)$).
 * Status: tested
 */
#pragma once

template<typename T>
struct BiVec { 
  vector<T> v;
  BiVec(int n, T x = {}) : v(2 * n, x) {}
  T& operator[](int i) { return v[2 * max(i, ~i) + (i < 0)]; }
  void resize(int n) { v.resize(2 * n); }
};