/**
 * Author: Lucian Bicsi
 * Date: 2020-11-28
 * License: CC0
 * Source: based on https://github.com/kmyk/competitive-programming-library
 * Description: Cooley-Tukey-like fft. For better precision, see "NTT.h".
 * Time: $O(N \log N)$
 * Status: stress-tested
 */
#pragma once

void DFT(vector<complex<double>> &a, bool rev) {
  int n = a.size(); auto b = a; 
  for (int step = n / 2; step; step /= 2) {
    for (int i = 0; i < n / 2; i += step) {
      auto wn = polar(1.0, 2.0 * M_PI * (rev ? -i : i) / n);
      for (int j = 0; j < step; ++j) {
        auto u = a[i * 2 + j], v = wn * a[i * 2 + j + step];
        b[i + j] = u + v; b[i + n / 2 + j] = u - v;
      }
    }
    swap(a, b);
  }
  if (rev) for (auto& x : a) x /= n;
}
