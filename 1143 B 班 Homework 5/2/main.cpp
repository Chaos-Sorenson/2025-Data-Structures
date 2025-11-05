#include <iostream>

constexpr int M = 1e5 + 10;

struct Edge {
  int u, v;
  long long w;
} e[M];

void down(int i, int n) {
  int j = 2 * i;
  while (j <= n) {
    if (j < n && e[j].w < e[j + 1].w)
      ++j;
    if (e[i].w >= e[j].w)
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

constexpr int N = 5e3 + 10;
int dsu[N], size[N];

int find(int x) {
  return dsu[x] == dsu[dsu[x]] ? dsu[x] : dsu[x] = find(dsu[x]);
}

void unite(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return;
  if (size[x] < size[y])
    std::swap(x, y);
  dsu[y] = x;
  size[x] += size[y];
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int n, m, k;
  std::cin >> n >> m >> k;

  int i;
  for (i = 1; i <= m; ++i)
    std::cin >> e[i].u >> e[i].v >> e[i].w;
  sort(m);

  for (i = 1; i <= n; ++i)
    dsu[i] = i, size[i] = 1;

  long long ans = 0;
  int selected = 0;
  for (i = 1; selected < n - 1 - k && i <= m; ++i)
    if (find(e[i].u) != find(e[i].v))
      ans += e[i].w, unite(e[i].u, e[i].v), ++selected;

  std::cout << ans;
  
  return 0;
}