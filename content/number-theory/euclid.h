/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds the Greatest Common Divisor to the integers $a$ and $b$. Euclid also finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
#pragma once

using ll = long long;

ll Euclid(ll a, ll b, ll &x, ll &y) {
	if (b) {
    ll d = Euclid(b, a % b, y, x);
		return y -= a/b * x, d;
  } else return x = 1, y = 0, a;
}

ll ModInv(ll a, ll p) {
  ll x, y;
  assert(Euclid(a, p, x, y) == 1);
  return x;
}
