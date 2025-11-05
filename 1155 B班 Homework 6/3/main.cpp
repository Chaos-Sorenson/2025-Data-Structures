#include <iostream>

constexpr int N = 2e5 + 10, M = 2e5 + 10;
int cnt, he[N], to[M], ne[M];

void add(int u, int v) {
  to[++cnt] = v;
  ne[cnt] = he[u];
  he[u] = cnt;
}

int w[N], bs[N];

void down(int *arr, int i, int n) {
  int j = 2 * i;
  while (j <= n) {
    if (j < n && arr[j + 1] < arr[j])
      ++j;
    if (arr[i] <= arr[j])
      return;
    std::swap(arr[i], arr[j]);
    i = j, j *= 2;
  }
}

void sort(int n, int &s) {
  int i, tmp[N];
  for (i = 1; i <= n; ++i)
    tmp[i] = w[i];
  for (i = n / 2; i >= 1; --i)
    down(tmp, i, n);
  s = 0;
  while (n > 0) {
    if (s == 0 || tmp[1] > bs[s])
      bs[++s] = tmp[1];
    tmp[1] = tmp[n];
    down(tmp, 1, --n);
  }
}

bool topo(int, int, int);

int main() {
  std::cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  std::cin >> n >> m >> k;

  int i, u, v, s;
  for (u = 1; u <= n; ++u)
    std::cin >> w[u];
  sort(n, s);
  for (i = 1; i <= m; ++i) {
    std::cin >> u >> v;
    add(u, v);
  }

  int l = 1, r = s + 1, md;
  bs[r] = -1;
  while (l < r) {
    md = (l + r) / 2;
    if (topo(n, k, bs[md]))
      r = md;
    else
      l = md + 1;
  }

  std::cout << bs[r];

  return 0;
}

int in[N], lv[N], q[N];
int i, u, v, frt, bk;

bool topo(int n, int k, int mx) {
  for (u = 1; u <= n; ++u)
    in[u] = 0, lv[u] = 0;

  for (u = 1; u <= n; ++u) {
    if (w[u] > mx)
      continue;
    for (i = he[u]; i != 0; i = ne[i]) {
      v = to[i];
      if (w[v] > mx)
        continue;
      ++in[v];
    }
  }

  frt = 0, bk = 0;
  for (u = 1; u <= n; ++u)
    if (in[u] == 0 && w[u] <= mx)
      q[++bk] = u, lv[u] = 1;
  
  while (frt < bk) {
    u = q[++frt];
    if (lv[u] >= k)
      return 1;
    for (i = he[u]; i != 0; i = ne[i]) {
      v = to[i];
      if (w[v] > mx)
        continue;
      lv[v] = std::max(lv[v], lv[u] + 1);
      if (--in[v] == 0)
        q[++bk] = v;
    }
  }

  for (u = 1; u <= n; ++u)
    if (in[u] > 0)
      return 1;
  return 0;
}