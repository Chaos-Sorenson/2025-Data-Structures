#include <iostream>

constexpr int MAXN = 1e6 + 5;
int a, b, c, t[MAXN << 2];

void d(int p) {
  if (t[p] & 1)
    t[p << 1] = t[p << 1 | 1] = t[p], t[p] &= ~1;
}

void mo(int p, int l, int r) {
  if (a <= l && r <= b) {
    t[p] = 1 << c | 1;
    return;
  }
  d(p);
  auto m = l + r >> 1;
  if (a <= m) mo(p << 1, l, m);
  if (b > m) mo(p << 1 | 1, m + 1, r);
  t[p] = (t[p << 1] | t[p << 1 | 1]) & ~1;
}

int q(int p, int l, int r) {
  if (a <= l && r <= b)
    return t[p];
  d(p);
  auto m = l + r >> 1;
  if (b <= m) return q(p << 1, l, m);
  if (a > m) return q(p << 1 | 1, m + 1, r);
  return q(p << 1, l, m) | q(p << 1 | 1, m + 1, r);
}

int ca(int s) {
  int r = 0;
  while (s > 0)
    r += s & 1, s >>= 1;
  return r;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int n, k, m;
  std::cin >> n >> k >> m;
  for (int i = 1; i < n << 2; ++i)
    t[i] = 2;
  char o;
  while (m--) {
    std::cin >> o;
    if (o == 'C') {
      std::cin >> a >> b >> c;
      mo(1, 1, n);
    }
    else {
      std::cin >> a >> b;
      std::cout << ca(q(1, 1, n) >> 1) << '\n';
    }
  }
}