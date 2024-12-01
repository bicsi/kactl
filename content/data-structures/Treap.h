/**
 * Author: Lucian Bicsi
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 *  It can support several operations, including lazy
 *  propagation (sample flip operation below).
 *  Can be made persistent, by making a copy at split/join
 *  functions.
 * Time: $O(\log N)$ expected time per operation
 * Warning: If making persistent, think twice if you need to
 * ditch priorities.
 */
#pragma once 

mt19937 rng(time(0));

struct Treap {
  struct Node {
    int l = 0, r = 0, sz = 0, pri = 0; // required
    ll key = 0; bool flip = 0;         // optional
  };
  vector<Node> T;
  
  Treap(int n) : T(n + 1) { 
    for (int i = 1; i <= n; ++i) 
      T[i].pri = rng(), pull(i);
  }
  void pull(int x) {
    if (!x) return;
    int l = T[x].l, r = T[x].r;
    T[x].sz = T[l].sz + T[r].sz + 1;
  }
  void push(int x) {
    if (!x) return;
    int l = T[x].l, r = T[x].r;
    if (T[x].flip) {
      swap(T[x].l, T[x].r);
      T[l].flip ^= 1, T[r].flip ^= 1;
      T[x].flip = 0;
    }
  }
  pair<int, int> Split(int x, auto&& is_lhs) {
    if (!x) return {0, 0};
    push(x); int l, r;
    if (is_lhs(x)) 
      tie(T[x].r, r) = Split(T[x].r, is_lhs), l = x;
    else 
      tie(l, T[x].l) = Split(T[x].l, is_lhs), r = x;
    pull(x); return {l, r};
  }
  pair<int, int> SplitByKey(int x, ll key) {
    return Split(x, [&](int y) { return T[y].key < key; });
  }
  pair<int, int> SplitByKth(int x, int k) {
    return Split(x, [&](int y) {
      int sz = T[T[y].l].sz + 1; 
      return k >= sz ? (k -= sz, 1) : 0;
    });
  }
  int Join(int l, int r) {
    if (!l || !r) return l + r;
    push(l); push(r);
    if (T[l].pri < T[r].pri)
      return T[l].r = Join(T[l].r, r), pull(l), l;
    return T[r].l = Join(l, T[r].l), pull(r), r;
  }
};