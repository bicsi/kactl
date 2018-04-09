/**
 * Author: Simon Lindholm (adapted by Lucian Bicsi)
 * Date: 2017-04-17
 * License: CC0
 * Description: Finds all biconnected components in an undirected multigraph, and
 *  runs a callback for the edges in each.
 *  In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle. HOWEVER, note that we are outputting bridges
 *  as BCC's here, because we might be interested in vertex bcc's, not edge
 *  bcc's.
 *
 *  To get the articulation points, look for vertices that are in more than 1 BCC.
 *  To get the bridges, look for biconnected components with one edge
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
#pragma once

struct BCC {
  vector<pair<int, int>> edges;
  vector<vector<int>> G;
  vector<int> enter, low, stk;
  
  BCC(int n) : G(n), enter(n, -1) {}
  
  int AddEdge(int a, int b) {
    int ret = edges.size();
    edges.emplace_back(a, b);
    G[a].push_back(ret);
    G[b].push_back(ret);
    return ret;
  }
  
  template<typename Iter>
  void Callback(Iter bg, Iter en) {
    for (Iter it = bg; it != en; ++it) {
      auto edge = edges[*it];
      // Do something useful
    }
  }
  
  void Solve() {
    for (int i = 0; i < (int)G.size(); ++i)
      if (enter[i] == -1) {
        dfs(i, -1);
      }
  }
  
  int timer = 0;
  int dfs(int node, int pei) {
    enter[node] = timer++;
    int ret = enter[node];
    
    for (auto ei : G[node]) if (ei != pei) {
      int vec = (edges[ei].first ^ edges[ei].second ^ node);
      if (enter[vec] != -1) {
        ret = min(ret, enter[vec]);
        if (enter[vec] < enter[node])
          stk.push_back(ei);
      } else {
        int sz = stk.size(), low = dfs(vec, ei);
        ret = min(ret, low);
        stk.push_back(ei);
        if (low >= enter[node]) {
          Callback(stk.begin() + sz, stk.end());
          stk.resize(sz);
        }
      }
    }
    return ret;
  }
};
