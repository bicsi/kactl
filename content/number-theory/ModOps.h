/**
 * Author: Lucian Bicsi
 * Description: ModOps class and operations for easy
 * modulo reduction.
 * Quick to code, but not fast.
 */
#pragma once

const int kMod = 1e9 + 7;

struct ModInt {
  long long n;
  
  ModInt(long long n = 0) : n(n % kMod) {}
  ModInt operator+(const ModInt& oth) { return n + oth.n; }
  ModInt operator-(const ModInt& oth) { return n - oth.n; }
  ModInt operator*(const ModInt& oth) { return n * oth.n; }
  long long get() { return n < 0 ? n + kMod : n; }
};

ModInt lgpow(ModInt b, int e) {
  ModInt r;
  for (r = 1; e; e /= 2, b = b * b)
    if (e % 2) r = r * b;
  return r;
}
ModInt inv(ModInt x) { return lgpow(x, kMod - 2); }
