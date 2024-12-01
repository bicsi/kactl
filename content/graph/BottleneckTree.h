/**
 * Author: Budau Adrian, Lucian Bicsi
 * Date: 2021-09-27
 * License: CC0
 * Source:
 * Description: Data structure for dynamic online incremental MST.
 * AddEdge returns the cost of the exchanged edge (maximum on path). 
 * Time: $O(???)$ (probably $O(\log n)$ amortized per added edge.
 * Status: tested on infoarena rutier, and brute force.
 */

struct BottleneckTree {
  vector<int> link;
  vector<ll> cost;

  BottleneckTree(int n) : link(n, 0), cost(n, INF) {
    link[0] = -1; cost[0]++;
  }
  ll AddEdge(int x, int y, ll c) {
    compress(x); reroot(x); compress(y); reroot(y);
    assert(link[x] == y);
    if (cost[x] > c) swap(cost[x], c);
    return c;
  }
  void compress(int x) {
    if (link[x] == -1) return;
    compress(link[x]);
    reroot(link[x], cost[x]);
    if (cost[link[x]] <= cost[x])
      link[x] = link[link[x]];
  }
  void reroot(int x, ll c = INF + 1) {
    int p = link[x];
    while (p != -1 && cost[p] <= c) {
      swap(cost[p], cost[x]);
      int g = link[p]; link[p] = x; p = g;
    }
    link[x] = p;
  }
};