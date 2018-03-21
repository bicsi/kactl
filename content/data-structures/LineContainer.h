/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form ax+b, 
 * and query maximum values at points x. 
 * For each line, also keeps a value p, which is the last (maximum) point 
 * for which the current line is dominant. 
 * (obviously, for the last line, p is infinity)
 *  Useful for dynamic programming.
 * Time: O(\log N)
 * Status: tested
 */
#pragma once
#include <bits/stdc++.h>

using namespace std;

using T = long long;

bool QUERY;
struct Line {
	mutable T a, b, p;
    T Eval(T x) const { return a * x + b; }
	bool operator<(const Line& o) const {
		return QUERY ? p < o.p : a < o.a;
	}
};

struct LineContainer : multiset<Line> {
	// for doubles, use kInf = 1/.0, div(a, b) = a / b
	const T kInf = numeric_limits<T>::max();
	T div(T a, T b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = kInf; return false; }
		if (x->a == y->a) x->p = x->b > y->b ? kInf : -kInf;
		else x->p = div(y->b - x->b, x->a - y->a);
		return x->p >= y->p;
	}
	void InsertLine(T a, T b) {
		auto nx = insert({a, b, 0}), it = nx++, pv = it;
		while (isect(it, nx)) nx = erase(nx);
		if (pv != begin() && isect(--pv, it)) isect(pv, it = erase(it));
		while ((it = pv) != begin() && (--pv)->p >= it->p)
			isect(pv, erase(it));
	}
	T EvalMax(T x) {
		assert(!empty());
		QUERY = 1; auto it = lower_bound({0,0,x}); QUERY = 0;
		return it->Eval(x);
	}
};
