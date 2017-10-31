/**
 * Author: Lucian Bicsi
 * License: CC0
 * Source: Russian page
 * Description: Pre-computation of modular inverses.
 * Assumes lim < kMod and that kMod is a prime.
 * Status: Works
 */
#pragma once
#include "ModOps.h"

vector<ModInt> ComputeInverses(int lim) {
  vector<ModInt> inv(lim + 1); inv[1] = 1;
  for (int i = 2; i <= lim; ++i) {
    inv[i] = ModInt(0) - ModInt(kMod / i) * inv[kMod % i];
  }
  return inv;
}
