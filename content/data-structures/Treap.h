/**
 * Author: Lucian Bicsi
 * Date: 2017-03-14
 * Source: folklore
 * Description: A short self-balancing tree. It acts as a
 *  sequential container with log-time splits/joins, and
 *  is easy to augment with additional data.
 *  It can support several operations, including lazy
 *  propagation (sample reverse operation below).
 *  Can be made persistent, by making a copy at pull function
 *  To transform into ordered set, uncomment line at (A)
 *  and delete the subtraction logic at (B).
 * Time: $O(\log N)$ expected time per operation
 */
#pragma once

namespace Treap {
  struct Node {
    int val, pri;
    int left = 0, right = 0, subsize = 0, lazy = 0;
    Node(int val, int pri) : val(val), pri(pri) {}
  };
  vector<Node> T(1, Node(-1, -1));
  
  int get_key(int node) {
    return T[T[node].left].subsize;
    // return T[node].val; (A)
  }
  
  int pull(int node) {
    if (node == 0) return 0;
    
    T[node].subsize = T[T[node].left].subsize
      + T[T[node].right].subsize + 1;
    
    return node;
  }
  
  int push(int node) {
    int& lazy = T[node].lazy;
    if (node == 0 or lazy == 0) return node;
    
    swap(T[node].left, T[node].right);
    T[T[node].left].lazy ^= lazy;
    T[T[node].right].lazy ^= lazy;
    lazy = 0;
    
    return node;
  }
  
  // Splits into < key and >= key
  pair<int, int> Split(int node, int key) {
    push(node);
    if (node == 0) return {0, 0};
    
    int l, r;
    if (get_key(node) < key) {              /* (B) */
      tie(l, r) = Split(T[node].right, key-get_key(node)-1);
      T[node].right = l;
      return {pull(node), r};
    } else {
      tie(l, r) = Split(T[node].left, key);
      T[node].left = r;
      return {l, pull(node)};
    }
  }
  
  // keys(node1) <= keys(node2) is REQUIRED
  int Join(int node1, int node2) {
    push(node1); push(node2);
    if (!node1) return node2;
    if (!node2) return node1;
    
    if (T[node1].pri > T[node2].pri) {
      T[node1].right = Join(T[node1].right, node2);
      return pull(node1);
    } else {
      T[node2].left = Join(node1, T[node2].left);
      return pull(node2);
    }
  }
  
  // Can be any foreach function
  void Dump(int node) {
    push(node);
    if (node == 0) return;
    
    Dump(T[node].left);
    cout << T[node].val << " ";
    Dump(T[node].right);
  }
  
  int Single(int value) {
    int node = T.size();
    T.push_back(Node(value, rand()));
    return pull(node);
  }
  
  // Only makes sense for cartesian tree
  tuple<int, int, int> Slice(int node, int b, int e) {
    int l, m, r;
    tie(m, r) = Split(node, e);
    tie(l, m) = Split(m, b);
    return make_tuple(l, m, r);
  }
  
  int Find(int node, int key) {
    int l, m, r;
    tie(l, m, r) = Slice(node, key, key + 1);
    assert(node == Join(l, Join(m, r)));
    return m;
  }
  
  int Insert(int node, int key, int value) {
    int l, r, m = Single(value);
    tie(l, r) = Split(node, key);
    return Join(l, Join(m, r));
  }
  
  int Reverse(int node) {
    T[node].lazy ^= 1;
    return push(node);
  }
  
}
