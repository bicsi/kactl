/**
 * Author: Lucian Bicsi
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

template<typename CB>
void BCC(vector<vector<int>>& graph, CB cb) {
  int timer = 0, n = graph.size();
  vector<int> val(n, -1);
  vector<tuple<int, int, int>> stk, cont;
  
  function<int(int, int)> dfs = [&](int node, int pei) {
    int ret; ret = val[node] = timer++;
    for (auto [vec, ei] : graph[node]) {
      if (ei == pei) continue;
      if (val[vec] != -1) {
        ret = min(ret, val[vec]);
        if (val[vec] < val[node])
          stk.emplace_back(node, vec, ei);
      } else {
        int sz = stk.size(), low = dfs(vec, ei);
        ret = min(ret, low);
        stk.emplace_back(node, vec, ei);
        if (low >= val[node]) {
          cont = {stk.begin() + sz, stk.end()}; 
          cb(cont); stk.resize(sz);
        }
      }
    }
    return ret;
  };
  for (int i = 0; i < n; ++i)
    if (val[i] == -1) 
      dfs(i, -1);
}