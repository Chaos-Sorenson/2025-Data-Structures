#include <iostream>

constexpr int N = 5e5 + 10, M = 5e5 + 10;

int edge_cnt, head[N], to[M], next[M];

void add(int u, int v) {
  to[++edge_cnt] = v;
  next[edge_cnt] = head[u];
  head[u] = edge_cnt;
}

int dfn[N], low[N], dfncnt;
int stk[N], in_stk[N], top;
int scc[N], sc;

void tarjan(int u) {
  low[u] = dfn[u] = ++dfncnt;
  stk[++top] = u, in_stk[u] = 1;
  int v;
  for (int i = head[u]; i != 0; i = next[i]) {
    v = to[i];
    if (dfn[v] == 0) {
      tarjan(v);
      low[u] = std::min(low[u], low[v]);
    } else if (in_stk[v] == 1) {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u]) {
    ++sc;
    do {
      v = stk[top];
      scc[v] = sc;
      in_stk[v] = 0;
    } while (stk[top--] != u);
  }
}



std::pair<int, int> dag_edges[M];
int ori_size;

void get_dag_edges(int n) {
  int u, v, i;
  for (u = 1; u <= n; ++u) {
    for (i = head[u]; i != 0; i = next[i]) {
      v = to[i];
      if (scc[u] == scc[v])
        continue;
      dag_edges[++ori_size] = {scc[u], scc[v]};
    }
  }
}

void down(int i, int n) {
  int j = 2 * i;
  while (j <= n) {
    if (j < n && dag_edges[j + 1] < dag_edges[j])
      ++j;
    if (dag_edges[i] <= dag_edges[j])
      return;
    std::swap(dag_edges[i], dag_edges[j]);
    i = j, j *= 2;
  }
}

int dag_edge_cnt, dag_head[N], dag_to[M], dag_next[M];

void dag_add(std::pair<int, int> p) {
  dag_to[++dag_edge_cnt] = p.second;
  dag_next[dag_edge_cnt] = dag_head[p.first];
  dag_head[p.first] = dag_edge_cnt;
}

void unique() {
  for (int i = ori_size / 2; i >= 1; --i)
    down(i, ori_size);
  for (int i = ori_size; i >= 1; --i) {
    if (i == ori_size || dag_edges[1] != dag_edges[i + 1])
      dag_add(dag_edges[1]);
    std::swap(dag_edges[1], dag_edges[i]);
    down(1, i - 1);
  }
}

int weight[N], flag[N];
int scc_sum[N], scc_flag[N];

void shrink(int n) {
  for (int u = 1; u <= n; ++u) {
    scc_sum[scc[u]] += weight[u];
    scc_flag[scc[u]] |= flag[u];
  }
  get_dag_edges(n);
  unique();
}

int rch[N], in_deg[N];

void get_in_deg(int s) {
  int q[N], front = 0, back = 0;
  q[++back] = s, rch[s] = 1;
  int u, v, i;
  while (front < back) {
    u = q[++front];
    for (i = dag_head[u]; i != 0; i = dag_next[i]) {
      v = dag_to[i];
      ++in_deg[v];
      if (rch[v] == 1)
        continue;
      rch[v] = 1;
      q[++back] = v;
    }
  }
}

int dp[N];

void solve(int s) {
  int u, v, i, res = -1;
  for (u = 1; u <= sc; ++u)
    dp[u] = -1;
  dp[s] = scc_sum[s];
  int q[N], front = 0, back = 0;
  q[++back] = s;
  while (front < back) {
    u = q[++front];
    if (scc_flag[u] == 1)
      res = std::max(res, dp[u]);
    for (i = dag_head[u]; i != 0; i = dag_next[i]) {
      v = dag_to[i];
      dp[v] = std::max(dp[v], dp[u] + scc_sum[v]);
      if (--in_deg[v] == 0)
        q[++back] = v;
    }
  }
  std::cout << res;
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);

  int n, m;
  std::cin >> n >> m;

  int u, v, i;
  for (i = 1; i <= m; ++i) {
    std::cin >> u >> v;
    add(u, v);
  }
  for (u = 1; u <= n; ++u)
    if (dfn[u] == 0)
      tarjan(u);

  for (u = 1; u <= n; ++u)
    std::cin >> weight[u];
  int s, p;
  std::cin >> s >> p;
  for (i = 1; i <= p; ++i) {
    std::cin >> u;
    flag[u] = 1;
  }
  shrink(n);

  get_in_deg(scc[s]);
  solve(scc[s]);

  return 0;
}