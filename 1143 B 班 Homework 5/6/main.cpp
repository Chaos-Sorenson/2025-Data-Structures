#include <iostream>

constexpr int N = 1e5 + 10, LOG2_N = 17;

int n;
int head[N], next[2 * N], to[2 * N];
int edge_cnt;
int parent[LOG2_N][N], child[N], sibling[N], dep[N];

void add_edge(int u, int v) {
  to[++edge_cnt] = v;
  next[edge_cnt] = head[u];
  head[u] = edge_cnt;

  to[++edge_cnt] = u;
  next[edge_cnt] = head[v];
  head[v] = edge_cnt;
}

void build_tree() {
  int queue[N];
  int begin = 0, end = 0;
  dep[1] = 1;
  queue[++end] = 1;

  int u, v, w, i;
  while(begin < end) {
    u = queue[++begin];

    for (i = head[u]; i != 0; i = next[i]) {
      v = to[i];
      if (v == parent[0][u])
        continue;

      parent[0][v] = u;
      dep[v] = dep[u] + 1;
      queue[++end] = v;

      if (child[u] == 0)
        child[u] = v;
      else
        sibling[w] = v;
      w = v;
    }
  }
}

int log2_n;

int lca(int u, int v) {
  if (dep[u] < dep[v])
    std::swap(u, v);

  for (int i = log2_n; i >= 0; --i)
    if (dep[parent[i][u]] >= dep[v])
      u = parent[i][u];

  if (u == v)
    return u;

  for (int i = log2_n; i >= 0; --i)
    if (parent[i][u] != parent[i][v])
      u = parent[i][u], v = parent[i][v];

  return parent[0][u];
}

int m;
int res[N], diff[N];

void dfs(int u) {
  res[u] = diff[u];

  for (int v = child[u]; v != 0; v = sibling[v]) {
    dfs(v);
    res[u] += res[v];
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::cin >> n >> m;

  int u, v, i;
  for (i = 1; i < n; ++i) {
    std::cin >> u >> v;
    add_edge(u, v);
  }
  build_tree();

  while (1 << log2_n <= n / 2)
    ++log2_n;

  for (i = 0; i < log2_n; ++i)
    for (u = 1; u <= n; ++u)
      parent[i + 1][u] = parent[i][parent[i][u]];

  for (i = 0; i < m; ++i) {
    std::cin >> u >> v;
    ++diff[u], ++diff[v];
    diff[lca(u, v)] -= 2;
  }

  dfs(1);

  int ans = 0;
  for (u = 2; u <= n; ++u) {
    if (res[u] == 0)
      ans += m;
    else if (res[u] == 1)
      ++ans;
  }
  std::cout << ans;

  return 0;
}