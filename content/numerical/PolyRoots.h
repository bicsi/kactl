/**
 * Author: Per Austrin
 * Date: 2004-02-08
 * License: CC0
 * Description: Finds the real roots to a polynomial.
 * Usage: Poly p = {2, -3, 1} // x^2 - 3x + 2 = 0
 * auto roots = GetRoots(p, -1e18, 1e18); // {1, 2}
 */
#pragma once

#include <bits/stdc++.h>
#include "Polynomial.h"

using namespace std;

vector<double> GetRoots(Poly p, double xmin, double xmax) {
	if (p.size() == 2) { return {-p.front() / p.back()}; }
	else {
		Poly d = Diff(p);
		vector<double> dr = GetRoots(d, xmin, xmax);
		dr.push_back(xmin - 1);
		dr.push_back(xmax + 1);
		sort(dr.begin(), dr.end());

		vector<double> roots;
		for (auto i = dr.begin(), j = i++; i != dr.end(); j = i++){
			double lo = *j, hi = *i, mid, f;
			bool sign = Eval(p, lo) > 0;
			if (sign ^ (Eval(p, hi) > 0)) {
				// for (int it = 0; it < 60; ++it) {
				while (hi - lo > 1e-8) {
					mid = (lo + hi) / 2, f = Eval(p, mid);
					if ((f <= 0) ^ sign) lo = mid;
					else hi = mid;
				}
				roots.push_back((lo + hi) / 2);
			}
		}
		return roots;
	}
}
