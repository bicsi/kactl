/**
 * Author: Lucian Bicsi
 * Date: 2017-08-14
 * License: CC0
 * Source: own work
 * Description: Aho-Corasick algorithm builds an automaton
 * for multiple pattern string matching
 * Time: $O(N \log \Sigma)$ where $N$ is the total length
 * Status: tested
 */

#pragma once

struct AhoCorasick {
  struct Node { int link; map<char, int> leg; };
  vector<Node> T;
  vector<int> q;
  int nodes = 1;

  AhoCorasick(int sz) : T(sz) {}

  // Adds a word to trie and returns the end node
  int Add(const string &s) {
    int node = 0;
    for (auto c : s) {
      auto &nxt = T[node].leg[c];
      if (nxt == 0) nxt = nodes++;
      node = nxt;
    }
    return node;
  }
  // Advances from a node with a character (like an automaton)
  int Go(int node, char c) {
    while (node != -1 && !T[node].leg.count(c))
      node = T[node].link;
    return (node == -1 ? 0 : T[node].leg[c]);
  }
  // Builds links
  void Build() {
    T[0].link = -1, q.push_back(0);
    for (int i = 0; i < (int)q.size(); ++i) {
      int node = q[i];
      for (auto [c, vec] : T[node].leg)
        T[vec].link = Go(T[node].link, c), q.push_back(vec);
    }
  }
};
