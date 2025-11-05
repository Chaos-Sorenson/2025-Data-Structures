#include <iostream>

constexpr int N = 5e3 + 10;

int adj[N][N];

int dfn[N], low[N], dfncnt;
int stk[N], in_stk[N], top;
int scc[N], sz[N], sc, sz_cnt;

int n;

void tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt;
  stk[++top] = u, in_stk[u] = 1;

  int v;
  for (v = 1; v <= n; ++v) {
    if (adj[u][v] == 0)
      continue;
    if (dfn[v] == 0) {
      tarjan(v);
      low[u] = std::min(low[u], low[v]);
    }
    else if (in_stk[v] == 1)
      low[u] = std::min(low[u], dfn[v]);
  }

  if (low[u] == dfn[u]) {
    scc[u] = ++sc, in_stk[u] = 0;
    sz_cnt = 1;
    while ((v = stk[top]) != u) {
      scc[v] = sc;
      in_stk[v] = 0;
      ++sz_cnt, --top;
    }
    sz[sc] = sz_cnt, --top;
  }
}

int dag[N][N], out_deg[N], rank[N], tot[N];

int main() {
  std::cin.tie(0)->sync_with_stdio(0);

  std::cin >> n;

  int i, j;
  char c;
  for (i = 1; i <= n; ++i) {
    for (j = 1; j <= n; ++j) {
      std::cin >> c;
      adj[i][j] = c - '0';
    }
  }

  for (i = 1; i <= n; ++i)
    if (dfn[i] == 0)
      tarjan(i);

  int u, v;
  for (u = 1; u <= n; ++u)
    for (v = 1; v <= n; ++v)
      if (adj[u][v] == 1 && dag[scc[u]][scc[v]] == 0 && scc[u] != scc[v])
        ++out_deg[scc[u]], dag[scc[u]][scc[v]] = 1;

  for (u = 1; u <= sc; ++u)
    rank[out_deg[u] + 1] = u;

  for (i = 1; i <= sc; ++i)
    tot[rank[i]] = tot[rank[i - 1]] + sz[rank[i]];

  for (u = 1; u <= n; ++u)
    std::cout << tot[scc[u]] - 1 << '\n';

  return 0;
}