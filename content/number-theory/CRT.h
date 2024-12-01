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

pair<ll, ll> CRT(ll m1, ll r1, ll m2, ll r2) {
  ll s, t;
  ll g = Euclid(m1, m2, s, t);
  if (r1 % g != r2 % g) return make_pair(0, -1);
  ll z = (s * r2 * m1 + t * r1 * m2) % (m1 * m2);
  if (z < 0) z += m1 * m2;
  return make_pair(m1 / g * m2, z / g);
}

pair<ll, ll> CRT(vector<ll> m, vector<ll> r) {
  pair<ll, ll> ret = make_pair(m[0], r[0]);
  for (int i = 1; i < (int)m.size(); i++) {
    ret = CRT(ret.first, ret.second, m[i], r[i]);
    if (ret.second == -1) break;
  }
  return ret;
}
