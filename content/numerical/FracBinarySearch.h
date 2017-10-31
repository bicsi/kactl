/**
 * Author: Lucian Bicsi
 * Description: Does binary search on fractions having an upper
 * bound on the numerator, given a predicate pred. The
 * predicate should be a monotonous function going from
 * negative to 0 to positive. The function will find a random
 * fraction f for which pred(f) = 0.
 * LOOPS WHEN NO SOLUTION (can be solved by checking
 * 2 consecutive iterations for no progress).
 * Complexity: O(\log(max_num))
 * Time: O(\log((b-a) / \epsilon))
 */
#pragma once

using int64 = int64_t;
struct Frac {
  int64 a, b;
};

template<typename Predicate>
Frac FracBinarySearch(int64 max_num, Predicate pred) {
  Frac lo{0, 1}, hi{1, 1}; // set to {1, 0} for [0...max_num)
  int sign = 1;
  
  if (pred(lo) == 0) return lo;
  while (true) {
    int64 adv = 0;
    bool down = false;
    
    for (int64 step = 1; step; down ? step /= 2 : step *= 2) {
      adv += step;
      
      Frac mid{lo.a * adv + hi.a, lo.b * adv + hi.b};
      if (mid.a > max_num or mid.b > max_num) {
        adv -= step; down = true; continue;
      }
      
      int64 res = pred(mid);
      if (res == 0) return mid;
      if (res * sign < 0) { adv -= step; down = true; }
    }
    
    hi.a += lo.a * adv;
    hi.b += lo.b * adv;
    sign = -sign;
    swap(lo, hi);
  }
}
