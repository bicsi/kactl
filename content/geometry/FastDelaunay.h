/**
 * Author: Philippe Legault
 * Date: 2016
 * License: MIT
 * Source: https://github.com/Bathlamos/delaunay-triangulation/
 * Description: Fast Delaunay triangulation.
 * Each circumcircle contains none of the input points.
 * There must be no duplicate points.
 * If all points are on a line, no triangles will be returned.
 * Should work for doubles as well, though there may be precision issues in 'InsideCircle'.
 * Returns triangles in counter-clockwise order.
 * Time: O(n \log n)
 * Status: stress-tested
 */

#include "Point.h"
#include "CircumCircle.h"

using Q = struct Quad*;
struct Quad {
  Q rot, o; int p = 0; bool mark;
  int& F() { return r()->p; }
  Q& r() { return rot->rot; }
  Q prev() { return rot->o->rot; }
  Q next() { return r()->prev(); }
} *H;

struct Delaunay {
  vector<Point> P; int n;

  Delaunay(vector<Point>& _P) : P(_P), n(_P.size()) {
    P.push_back(P.back() + Point{1, 0}); // any point not in P
  }
  Q add(int orig, int dest) {
    Q r = H ?: new Quad{new Quad{new Quad{new Quad{0}}}};
    H = r->o; r->r()->r() = r;
    for (int i = 0; i < 4; ++i) 
      r = r->rot, r->p = n, r->o = i & 1 ? r : r->r();
    r->p = orig; r->F() = dest;
    return r;
  }
  void splice(Q a, Q b) {
    swap(a->o->rot->o, b->o->rot->o); 
    swap(a->o, b->o);
  }
  Q connect(Q a, Q b) {
    Q q = add(a->F(), b->p);
    splice(q, a->next());
    splice(q->r(), b);
    return q;
  }
  #define H(e) P[e->F()], P[e->p]
  #define valid(e) (det(P[e->F()], H(base)) > 0) 
  pair<Q, Q> divide(int b, int e) {
    if (e - b <= 3) {
      Q qa = add(b, b + 1), qb = add(b + 1, e - 1);
      if (e - b == 2) return {qa, qa->r()};
      splice(qa->r(), qb);
      auto side = det(P[b], P[b + 1], P[b + 2]);
      Q qc = side ? connect(qb, qa) : 0;
      return {side < 0 ? qc->r() : qa, 
              side < 0 ? qc : qb->r()}; 
    }
    Q A, B, ra, rb;
    int m = (b + e) / 2;
    tie(ra, A) = divide(b, m); 
    tie(B, rb) = divide(m, e);
    while ((det(P[B->p], H(A)) < 0 && (A = A->next())) ||
          (det(P[A->p], H(B)) > 0 && (B = B->r()->o)));
    Q base = connect(B->r(), A);
    if (A->p == ra->p) ra = base->r();
    if (B->p == rb->p) rb = base;
  
    #define DEL(e, init, dir) Q e = init->dir; if (valid(e)) \
      while (InsideCircum(P[e->dir->F()], H(base), P[e->F()]) > 0) { \
          Q t = e->dir; \
          splice(e, e->prev()); \
          splice(e->r(), e->r()->prev()); \
          e->o = H; H = e; e = t; \
      }
    while (true) {
      DEL(LC, base->r(), o);  DEL(RC, base, prev());
      if (!valid(LC) && !valid(RC)) break;
      if (!valid(LC) || (valid(RC) && 
          InsideCircum(H(RC), H(LC)) > 0))
        base = connect(RC, base->r());
      else
        base = connect(base->r(), LC->r());
    }
    return {ra, rb};
  }
  
  vector<array<int, 3>> Triangulate() {
    if (P.size() < 2) return {};
    Q e = divide(0, n).first;
    while (det(P[e->o->F()], P[e->F()], P[e->p]) < 0) e = e->o;
    vector<Q> q = {e};
    vector<array<int, 3>> ret;
    for (int qi = 0; qi < (int)q.size(); ++qi) {
      if ((e = q[qi])->mark) continue;
      ret.emplace_back();
      for (int i = 0; i < 3; ++i) {
        e->mark = 1; ret.back()[i] = e->p;
        q.push_back(e->r()); e = e->next();
      }
    }
    ret.erase(ret.begin());
    return ret;
  }
};