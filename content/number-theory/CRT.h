/**
 * Author: Stanford
 * Date: 2003-02-16
 * Description: Chinese Remainder Theorem.
 *
 * Find z such that $z \% m_{1} = r_{1}, z \% m_{2} = r_{2}$.
 * Here, z is unique modulo M = lcm(m1, m2).
 * The vector version solves a system of equations of type
 * $z \% m_{i} = p_{i}$. On output, return \{ 0, -1 \} .
 * Note that all numbers must be less than
 * $2^{31}$ if you have type unsigned long long.
 * Status: Works
 * Time: $\log(m + n)$
 */
#pragma once

#include "Euclid.h"

pair<int, int> CRT(int m1, int r1, int m2, int r2) {
  int s, t;
  int g = Euclid(m1, m2, s, t);
  if (r1 % g != r2 % g) return make_pair(0, -1);
  int z = (s * r2 * m1 + t * r1 * m2) % (m1 * m2);
  if (z < 0) z += m1 * m2;
  return make_pair(m1 * m2 / g, z / g);
}

pair<int, int> CRT(vector<int> m, vector<int> r) {
  pair<int, int> ret = make_pair(m[0], r[0]);
  for (int i = 1; i < m.size(); i++) {
    ret = CRT(ret.first, ret.second, m[i], r[i]);
    if (ret.second == -1) break;
  }
  return ret;
}
