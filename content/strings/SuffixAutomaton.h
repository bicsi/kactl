/**
 * Author: Lucian Bicsi
 * Date: 2017-08-14
 * License: CC0
 * Source: own work
 * Description: Builds an automaton of all the suffixes
 * of a given string (online from left to right).
 * For each character c, do sa.ConsumeChar(c)
 * You can change char to int and add negative numbers
 * to support multiple strings.
 * Time: $O(log(sigma))$ amortized per character added
 * Status: tested
 */
#pragma once
#include <bits/stdc++.h>

using namespace std;

struct SuffixAutomaton {
  struct Node {
    int link, len;
    map<char, int> leg;
  };
  vector<Node> T;
  int last = 0, nodes = 1;

  SuffixAutomaton(int sz) : T(2 * sz + 1) {
    T[0].link = -1;
    T[0].len = 0;
  }

  // Adds another character to the automaton
  // and returns the node of the whole new string
  // (the suffixes of that are parents in the link tree)
  int ConsumeChar(char c) {
    // Add state for whole string
    int cur = nodes++, node = last;
    T[cur].len = T[last].len + 1;
    T[cur].link = 0;

    // Add transitions to all suffixes which do not have one
    // already
    while (node != -1 && T[node].leg.count(c) == 0) {
      T[node].leg[c] = cur;
      node = T[node].link;
    }

    if (node != -1) {
      int old = T[node].leg[c];

      if (T[old].len == T[node].len + 1) {
        T[cur].link = old;
      } else {
        int clone = nodes++;

        T[clone].leg = T[old].leg;
        T[clone].len = T[node].len + 1;
        T[clone].link = T[old].link;
        T[old].link = T[cur].link = clone;

        while (node != -1 && T[node].leg[c] == old) {
          T[node].leg[c] = clone;
          node = T[node].link;
        }
      }
    }
    return last = cur;
  }
  
  // Runs through the automaton
  int Go(int node, char c) {
    while (node != -1 && T[node].leg.count(c) == 0)
      node = T[node].link;
    return (node == -1 ? 0 : T[node].leg[c]);
  }
};
