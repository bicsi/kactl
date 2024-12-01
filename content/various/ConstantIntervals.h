/**
 * Author: Simon Lindholm
 * Date: 2015-03-20
 * License: CC0
 * Source: me
 * Description: Split a monoene function on [b, e) into a
 *  minimal set of half-open intervals on which it has the
 *  same value.
 *  Runs a callback cb for each such interval.
 * Usage: ConstantIntervals(0, v.size(), [\&](int x){return v[x];}, [\&](int lo, int hi, T val){...});
 * Time: O(k\log\frac{n}{k})
 * Status: tested
 */
#pragma once

template<class Func, class Callback, class T>
void recurse(int b, int e, Func&& f, Callback&& cb,
             int& i, T& p, T q) {
  if (p == q) return;
  if (b == e) {
    cb(i, e, p);
    i = e; p = q;
  } else {
    int m = (b + e) / 2;
    recurse(b, m, f, cb, i, p, f(m));
    recurse(m + 1, e, f, cb, i, p, q);
  }
}
template<class Func, class Callback>
void ConstantIntervals(int b, int e, Func f, Callback cb) {
  if (e <= b) return;
  int i = b; auto p = f(i), q = f(e - 1);
  recurse(b, e - 1, f, cb, i, p, q);
  cb(i, e, q);
}
