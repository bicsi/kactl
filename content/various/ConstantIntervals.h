/**
 * Author: Simon Lindholm
 * Date: 2015-03-20
 * License: CC0
 * Source: me
 * Description: Split a monotone function on [from, to) into a
 *  minimal set of half-open intervals on which it has the
 *  same value.
 *  Runs a callback cb for each such interval.
 * Usage: ConstantIntervals(0, v.size(), [\&](int x){return v[x];}, [\&](int lo, int hi, T val){...});
 * Time: O(k\log\frac{n}{k})
 * Status: tested
 */
#pragma once

template<class Func, class Callback, class T>
void recurse(int from, int to, Func f, Callback cb,
             int& i, T& p, T q) {
	if (p == q) return;
	if (from == to) {
		cb(i, to, p);
		i = to; p = q;
	} else {
		int mid = (from + to) / 2;
		recurse(from, mid, f, cb, i, p, f(mid));
		recurse(mid + 1, to, f, cb, i, p, q);
	}
}
template<class Func, class Callback>
void ConstantIntervals(int from, int to, Func f, Callback cb) {
	if (to <= from) return;
	int i = from; auto p = f(i), q = f(to - 1);
	recurse(from, to - 1, f, cb, i, p, q);
	cb(i, to, q);
}
