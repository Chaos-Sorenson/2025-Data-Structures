#include <iostream>
#include <climits>

constexpr int M = 5e4 + 10;

struct Edge {
  int u, v, w;
} e[M];

void down(int i, int n) {
  int j = 2 * i;
  while (j <= n) {
    if (j < n && e[j + 1].w < e[j].w)
      ++j;
    if (e[i].w <= e[j].w)
      return;
    std::swap(e[i], e[j]);
    i = j, j *= 2;
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

constexpr int N = 1e4 + 10;
int dsu[N], size[N];

int Find(int x) {
  return dsu[x] == x ? x : dsu[x] = Find(dsu[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (size[x] > size[y])
    std::swap(x, y);
  dsu[x] = y;
}

int edge_cnt, head[N], to[2 * N], next[2 * N], weight[2 * N];

void add_edge(int u, int v, int w) {
  Union(u, v);

  to[++edge_cnt] = v;
  next[edge_cnt] = head[u];
  head[u] = edge_cnt;
  weight[edge_cnt] = w;

  to[++edge_cnt] = u;
  next[edge_cnt] = head[v];
  head[v] = edge_cnt;
  weight[edge_cnt] = w;
}

constexpr int LOG2N = 14;
int dep[N], fa[LOG2N][N], min[LOG2N][N];

int q[N];
int front, back;

void build_tree(int rt) {
  if (dep[rt] != 0)
    return;
  
  front = 0, back = 1;
  q[1] = rt;

  int u, v, i;
  while (front < back) {
    u = q[++front];

    for (i = head[u]; i != 0; i = next[i]) {
      if ((v = to[i]) == fa[0][u])
        continue;
      
      q[++back] = v;
      dep[v] = dep[u] + 1;
      fa[0][v] = u;
      min[0][v] = weight[i];
    }
  }
}

int log2n;

int lca(int u, int v) {
  int res = INT_MAX;

  if (dep[u] < dep[v])
    std::swap(u, v);

  for (int i = log2n; i >= 0; --i) {
    if (dep[u] - dep[v] >= 1 << i) {
      res = std::min(res, min[i][u]);
      u = fa[i][u];
    }
  }

  if (u == v)
    return res;

  for (int i = log2n; i >= 0; --i) {
    if (fa[i][u] == fa[i][v])
      continue;
    res = std::min(res, std::min(min[i][u], min[i][v]));
    u = fa[i][u], v = fa[i][v];
  }

  return fa[0][u] == 0 ? -1 : std::min(res, std::min(min[0][u], min[0][v]));
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  int n, m;
  std::cin >> n >> m;

  int i;
  for (i = 1; i <= m; ++i)
    std::cin >> e[i].u >> e[i].v >> e[i].w;
  sort(m);

  for (i = 1; i <= n; ++i)
    dsu[i] = i;

  int u, v, w;
  for (i = 1; i <= m; ++i) {
    u = e[i].u, v = e[i].v, w = e[i].w;

    if (Find(u) != Find(v))
      add_edge(u, v, w);
  }

  for (i = 1; i <= n; ++i)
    build_tree(i);

  while (1 << (log2n + 1) < n)
    ++log2n;

  for (i = 0; i < log2n; ++i) {
    for (u = 1; u <= n; ++u) {
      fa[i + 1][u] = fa[i][fa[i][u]];
      min[i + 1][u] = std::min(min[i][u], min[i][fa[i][u]]);
    }
  }

  int q;
  std::cin >> q;
  for (i = 1; i <= q; ++i) {
    std::cin >> u >> v;
    std::cout << lca(u, v) << '\n';
  }

  return 0;
}