#include <iostream>
#include <iomanip>
#include <cmath>

constexpr int P = 510;
int x[P], y[P];

struct edge {
  int u, v;
  double d;
} e[P * (P - 1) / 2];

void down(int i, int n) {
  int j = 2 * i;
  while (j <= n) {
    if (j < n && e[j].d < e[j + 1].d)
      ++j;
    if (e[i].d >= e[j].d)
      return;
    std::swap(e[i], e[j]);
    i = j;
    j = 2 * i;
  }
}

void sort(int n) {
  for (int i = n / 2; i >= 1; --i)
    down(i, n);
  while (n > 1) {
    std::swap(e[1], e[n]);
    down(1, --n);
  }
}

int dsu[P], size[P];

int Find(int x) {
  return dsu[x] == x ? x : dsu[x] = Find(dsu[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (size[x] > size[y])
    std::swap(x, y);
  dsu[x] = y;
  size[y] += size[x];
}

int s, p;

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::cin >> s >> p;
  if (s >= p - 1) {
    std::cout << std::fixed << std::setprecision(2) << 0.0;
    return 0;
  }

  int i, j, dx, dy;
  for (i = 1; i <= p; ++i) {
    std::cin >> x[i] >> y[i];
    dsu[i] = i, size[i] = 1;
  }
  for (i = 2; i <= p; ++i)
    for (j = 1; j < i; ++j) {
      dx = x[i] - x[j], dy = y[i] - y[j];
      e[(i - 1) * (i - 2) / 2 + j] = {i, j, sqrt(dx * dx + dy * dy)};
    }
  sort(p * (p - 1) / 2);

  double d = 0;
  int cnt = p;
  for (i = 1; cnt > s; ++i) {
    if (Find(e[i].u) == Find(e[i].v))
      continue;
    d = e[i].d;
    Union(e[i].u, e[i].v);
    --cnt;
  }
  std::cout << std::fixed << std::setprecision(2) << d;
  return 0;
}