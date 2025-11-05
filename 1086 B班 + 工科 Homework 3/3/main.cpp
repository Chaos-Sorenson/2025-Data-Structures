#include <iostream>

int n, i, h, r, s, a[100001], b[100001], c[100001];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n;
  for (i = 1; i <= n; ++i) {
    std::cin >> h;
    a[h] = i, c[i] = i & -i;
  }
  i = 0;
  for (h = 1; i < n; ++h) if (a[h])
    b[a[h]] = ++i;

  ++i; while (--i) {
    h = b[i], r = 0; while (h)
      r += c[h], h -= h & -h;
    r = 3 * (i - r), h = n - b[i],
    s += h > r || h << 1 < r;
    h = b[i]; while (h <= n)
      --c[h], h += h & -h;
  }
  std::cout << s;
  return 0;
}