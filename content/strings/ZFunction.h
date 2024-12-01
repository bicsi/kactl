/**
 * Author: 
 * Source: https://cp-algorithms.com/string/z-function.html
 * Description: Given a string s, computes the length of the
 * longest common prefix of s[i..] and s[0..] for each i > 0 !!
 * Usage:
 *  ZFunction("abacaba") => {0, 0, 1, 0, 3, 0, 1}
 * Time: O(N)
 * Status: Tested on infoarena (on strmatch)
 */
#pragma once

vector<int> ZFunction(string s) {
  int n = s.size();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) z[i] = min (r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}