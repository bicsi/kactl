/**
 * Author: Lucian Bicsi
 * Date: 2020-12-13
 * License: CC0
 * Description: Easy to implement and fast meldable heap.
 * Time: O(\log N) per operation
 * Status: Tested on yosupo judge and DirectedMST.
 */

struct SkewHeap {
  struct Node { ll key, lazy = 0; int l = -1, r = -1; };
  vector<Node> T;

  void push(int x) {
    if (x == -1 || !T[x].lazy) return;
    for (int y : {T[x].l, T[x].r}) if (y != -1) 
      T[y].lazy += T[x].lazy;
    T[x].key += T[x].lazy, T[x].lazy = 0;
  }
  // Make new node. Returns its index. Indexes go 0, 1, ...
  int New(ll key) { 
    T.push_back(Node{key}); 
    return (int)T.size() - 1;
  }
  // Increment all values in heap p by v
  void Add(int x, ll v) { if (~x) T[x].lazy += v, push(x); }
  // Merge heaps a and b
  int Merge(int a, int b) {
    if (b == -1 || a == -1) return a + b + 1;
    if (T[a].key > T[b].key) swap(a, b);
    int &l = T[a].l, &r = T[a].r;
    push(r); swap(l, r); l = Merge(l, b);
    return a;
  }
  void Pop(int& x) { x = Merge(T[x].l, T[x].r); }
  ll Get(int x) { return T[x].key; }
};