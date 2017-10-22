/**
 * Author: Lucian Bicsi
 * Description: pi[x] is the length of the longest prefix of s
 * that ends at x (exclusively), other than s[0..x) itself.
 * This is used by Match() to find all occurences of a string.
 * Time: O(N)
 * Status: Tested on infoarena
 * Usage:
 *  ComputePi("alabala") => {-1, 0, 0, 1, 0, 1, 2, 3}
 *  Match("atoat", "atoatoat") => {4, 7}
 */
#pragma once

vector<int> ComputePi(string s) {
  int n = s.size();
  vector<int> pi(n + 1, -1);
  
  for (int i = 0; i < n; ++i) {
    int j = pi[i];
    while (j != -1 && s[j] != s[i]) j = pi[j];
    pi[i + 1] = j + 1;
  }
  
  return pi;
}

vector<int> Match(string text, string pat) {
  vector<int> pi = ComputePi(pat), ret;
  int j = 0;
  
  for (int i = 0; i < (int)text.size(); ++i) {
    while (j != -1 && pat[j] != text[i]) j = pi[j];
    if (++j == pat.size())
      ret.push_back(i), j = pi[j];
  }
  return ret;
}

