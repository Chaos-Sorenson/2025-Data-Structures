#include <iostream>

constexpr int N = 5e4 + 10, LOG2_N = 17;

int n, e_cnt;
int he[N], ne[2 * N], to[2 * N], len[2 * N], fa[LOG2_N][N], dis[LOG2_N][N], dep[N];

void add_edge(int u, int v, int l) {
  to[++e_cnt] = v;
  ne[e_cnt] = he[u];
  he[u] = e_cnt;
  len[e_cnt] = l;

  to[++e_cnt] = u;
  ne[e_cnt] = he[v];
  he[v] = e_cnt;
  len[e_cnt] = l;
}

void build_tree() {
  int q[N];
  int begin = 0, end = 0;
  dep[1] = 1;
  q[++end] = 1;

  int u, v, w, i;
  while (begin < end) {
    u = q[++begin];
    for (i = he[u]; i != 0; i = ne[i]) {
      v = to[i];
      if (v == fa[0][u])
        continue;
      fa[0][v] = u;
      dis[0][v] = len[i];
      dep[v] = dep[u] + 1;
      q[++end] = v;
    }
  }
}

int log2_n;

std::pair<int, int> lca(int u, int v) {
  if (dep[u] < dep[v])
    std::swap(u, v);

  int d = 0;
  for (int i = log2_n; i >= 0; --i)
    if (dep[fa[i][u]] >= dep[v]) {
      d += dis[i][u];
      u = fa[i][u];
    }

  if (u == v)
    return std::pair<int, int>(u, d);

  for (int i = log2_n; i >= 0; --i)
    if (fa[i][u] != fa[i][v]) {
      d += dis[i][u] + dis[i][v];
      u = fa[i][u];
      v = fa[i][v];
    }

  return std::pair<int, int>(fa[0][u], d + dis[0][u] + dis[0][v]);
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::cin >> n;
  int u, v, l, i;
  for (i = 1; i < n; ++i) {
    std::cin >> u >> v >> l;
    add_edge(u, v, l);
  }
  build_tree();

  while (1 << (log2_n + 1) < n)
    ++log2_n;
  for (i = 0; i < log2_n; ++i)
    for (u = 1; u <= n; ++u) {
      fa[i + 1][u] = fa[i][fa[i][u]];
      dis[i + 1][u] = dis[i][u] + dis[i][fa[i][u]];
    }

  int Q, w, ans;
  std::pair<int, int> p;
  for (std::cin >> Q; Q > 0; --Q) {
    std::cin >> u >> v >> w;

    p = lca(u, v);
    ans = p.second + lca(p.first, w).second;

    p = lca(v, w);
    ans = std::min(ans, p.second + lca(p.first, u).second);

    p = lca(w, u);
    ans = std::min(ans, p.second + lca(p.first, v).second);

    std::cout << ans << '\n';
  }
  return 0;
}