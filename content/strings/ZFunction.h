/**
 * Author: 
 * Source: http://codeforces.com/blog/entry/3107
 * Description: Given a string s, computes the length of the
 * longest common prefix of s[i..] and s[0..] for each i > 0 !!
 * Usage:
 *  Zfunction("abacaba") => {0, 0, 1, 0, 3, 0, 1}
 * Time: O(N)
 * Status: Tested on infoarena (on strmatch)
 */
#pragma once
#include <bits/stdc++.h>
using namespace std;

vector<int> ZFunction(string s) {
  int n = s.size();
  vector<int> z(n, 0);
  int L = 0, R = 0;
  for (int i = 1; i < n; i++) {
    if (i > R) {
      L = R = i;
      while (R < n && s[R - L] == s[R]) R++;
      z[i] = R - L; R--;
    } else {
      int k = i-L;
      if (z[k] < R - i + 1) z[i] = z[k];
      else {
        L = i;
        while (R < n && s[R - L] == s[R]) R++;
        z[i] = R - L; R--;
      }
    }
  }
  return z;
}

