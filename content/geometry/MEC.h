/**
 * Author: Andrew He, chilli
 * Date: 2019-05-07
 * License: CC0
 * Source: folklore
 * Description: Computes the minimum circle that encloses a set of points.
 * Time: expected O(N)
 * Status: stress-tested
 */

Circle MEC(vector<Point>& pts) {
  assert(pts.size());
  shuffle(pts.begin(), pts.end(), rng);
  int n = pts.size();
  Point c = pts[0]; double r = 0;
  for (int i = 0; i < n; ++i) {
    if (abs(c - pts[i]) < r * (1 + EPS)) continue;
    c = pts[i]; r = 0.;
    for (int j = 0; j < i; ++j) {
      if (abs(c - pts[j]) < r * (1 + EPS)) continue;
      c = (pts[i] + pts[j]) * 0.5; r = abs(c - pts[i]);
      for (int k = 0; k < j; ++k) {
        if (abs(c - pts[k]) < r * (1 + EPS)) continue;
        c = CircumCenter(pts[i], pts[j], pts[k]);
        r = abs(c - pts[i]);
      }
    }
  }
  return {c, r};
}