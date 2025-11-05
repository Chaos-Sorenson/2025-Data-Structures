#include <iostream>

constexpr int MAXN = 100001, MOD = 1000000007;
long long s[MAXN], t[MAXN];
int N, Q, i, x, w, v;

long long query(const int m) {
  long long sum1 = 0, sum2 = 0;
  int k = m - 1;
  while (k)
    sum1 = (sum1 + s[k]) % MOD,
    sum2 = (sum2 + t[k]) % MOD,
    k -= k & -k;
  return (m * sum1 - sum2) % MOD;
}

void update(int k, const long long v1) {
  const long long v2 = k * v1;
  while (k <= N)
    s[k] += v1,
    t[k] += v2,
    k += k & -k;
}

int main() {
  std::cin >> N >> Q; ++Q;

  for (i = 1; i <= N; ++i) {
    std::cin >> s[i];
    t[i] = t[i - 1] + i * (s[i] - s[i - 1]);
  }

  for (i = N; i; --i)
    v = i - (i & -i),
    s[i] = s[i] - s[v],
    t[i] = t[i] - t[v];

  while (--Q) {
    std::cin >> i >> x >> w;

    if (i == 1)
      std::cout << ((query(x + w) - query(x)) % MOD + MOD) % MOD << '\n';


    else {
      std::cin >> v;
      update(x, v),
      update(x + w, -v);
    }
  }
  return 0;
}