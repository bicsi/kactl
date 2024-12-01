#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll INF = 2e18;

ll Ceil(ll a, ll b) {
	assert(b > 0);
	return a / b + (a % b > 0);
}
ll Floor(ll a, ll b) {
	assert(b > 0);
	return a / b - (a % b < 0);
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
}
