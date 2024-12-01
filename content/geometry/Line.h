/**
 * Author: Lucian Bicsi
 * License: CC0
 * Description: Line operations. 
 * Warning: Line equation is kept as
 * $ax + by = c$ (unlike the usual $ax + by + c = 0$)
 * Status: Works fine, hopefully.
 */
#pragma once

using T = int; 
using T2 = long long;
using T4 = __int128_t;
const T2 INF = 4e18;

struct Line { T a, b; T2 c; };

bool half(Line m) { return m.a < 0 || m.a == 0 && m.b < 0; };
void normalize(Line& m) {
  T2 g = __gcd((T2)__gcd(abs(m.a), abs(m.b)), abs(m.c));
  if (half(m)) g *= -1;
  m.a /= g, m.b /= g, m.c /= g;
}
// Sorts halfplanes in clockwise order. 
// To sort lines, normalize first (gcd logic not needed).
bool operator<(Line m, Line n) {
  return make_pair(half(m), (T2)m.b * n.a) < 
         make_pair(half(n), (T2)m.a * n.b);
}
Line LineFromPoints(T x1, T y1, T x2, T y2) {
  T a = y1 - y2, b = x2 - x1;
  T2 c = (T2)a * x1 + (T2)b * y1;
  return {a, b, c}; // halfplane points to the left of vec.
}