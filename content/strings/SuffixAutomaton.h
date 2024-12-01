/**
 * Author: Lucian Bicsi
 * Date: 2017-08-14
 * License: CC0
 * Source: own work
 * Description: Builds an automaton of all the suffixes
 * of a given string (online from left to right).
 * To support multiple strings/trie, you can add characters
 * in BFS order of trie and it should work.
 * Time: $O(\log \Sigma)$ amortized per character added
 * Usage: last = 0; for (auto c : s) last = SA.Add(last, c);
 * Status: tested
 */
#pragma once

struct SuffixAutomaton {
  struct Node {
    int len, link;
    map<char, int> leg; // Can use array<int, 26> instead.
  };
  vector<Node> T = {{0, -1, {}}};
  // Adds another character to the automaton.
  int Add(int last, char c) {
    int node = last, cur = T.size(); 
    T.push_back({T[last].len + 1, 0, {}});
    while (node != -1 && !T[node].leg[c])
      T[node].leg[c] = cur, node = T[node].link;
    if (node != -1) {
      int old = T[node].leg[c], len = T[node].len + 1;
      assert(T[cur].len >= T[old].len);
      if (T[old].len == len) {
         T[cur].link = old;
      } else {
        int clone = T.size(); 
        T.push_back({len, T[old].link, T[old].leg});
        T[old].link = T[cur].link = clone;
        while (node != -1 && T[node].leg[c] == old) 
          T[node].leg[c] = clone, node = T[node].link;
      }
    }
    return cur;
  }
};