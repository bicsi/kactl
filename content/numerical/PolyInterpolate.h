/**
 * Author: Simon Lindholm
 * Date: 2017-05-10
 * License: CC0
 * Source: Wikipedia
 * Description: Given $n$ points (x[i], y[i]), computes an n-1-degree polynomial $p$ that
 *  passes through them: $p(x) = a[0]*x^0 + ... + a[n-1]*x^{n-1}$.
 *  For numerical precision, pick $x[k] = c*\cos(k/(n-1)*\pi), k=0 \dots n-1$.
 * Time: O(n^2)
 */
#pragma once
#include <bits/stdc++.h>
#include "Polynomial.h"

using namespace std;

Poly Interpolate(vector<TElem> x, vector<TElem> y) {
	int n = x.size();
	Poly res(n), temp(n);
	for (int k = 0; k < n; ++k)
	  for (int i = k + 1; i < n; ++i)
		y[i] = (y[i] - y[k]) / (x[i] - x[k]);
	TElem last = 0; temp[0] = 1;
	for (int k = 0; k < n; ++k)
	for (int i = 0; i < n; ++i) {
		res[i] = res[i] + y[k] * temp[i];
		swap(last, temp[i]);
		temp[i] = temp[i] - last * x[k];
	}
	return res;
}
