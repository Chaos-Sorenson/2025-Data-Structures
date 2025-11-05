#include <iostream>

constexpr int N = 2.5e4 + 10; 
int dsu[N], sz[N];

void dsu_ini(int n) {
  for (int x = 1; x <= n; ++x)
    dsu[x] = x, sz[x] = 1;
}

int find(int x) {
  return dsu[x] == dsu[dsu[x]] ? dsu[x] : dsu[x] = find(dsu[x]);
}

void unite(int x, int y) {
  x = find(x), y = find(y);
  if (x == y)
    return;
  if (sz[x] < sz[y])
    std::swap(x, y);
  dsu[y] = x;
  sz[x] += sz[y];
}

constexpr int M = 5e4 + 10;
int cnt, head[N], to[2 * M], nxt[2 * M], weight[2 * M];

void add(int u, int v, int w) {
  to[++cnt] = v;
  nxt[cnt] = head[u];
  head[u] = cnt;
  weight[cnt] = w;
}

int cc_head[N], cc_nxt[N];

void cc_add(int u) {
  cc_nxt[u] = cc_head[find(u)];
  cc_head[dsu[u]] = u;
}

int p_head[N], p_to[M], p_nxt[M], p_weight[M];

void p_add(int u, int v, int w) {
  p_to[++cnt] = v;
  p_nxt[cnt] = p_head[u];
  p_head[u] = cnt;
  p_weight[cnt] = w;
}

int rch[N], in_deg[N];
int q[N], fr, bk;

void get_in_deg(int s) {
  q[++bk] = s;
  int u, v, i, another_s;
  while (fr < bk) {
    s = q[++fr];
    for (u = cc_head[s]; u != 0; u = cc_nxt[u]) {
      for (i = p_head[u]; i != 0; i = p_nxt[i]) {
        v = p_to[i];
        another_s = dsu[v];
        ++in_deg[another_s];
        if (rch[another_s] == 1)
          continue;
        rch[another_s] = 1;
        q[++bk] = another_s;
      }
    }
  }
}

constexpr int INF = 2147483647;
int dis[N];

void dis_ini(int n, int s) {
  for (int u = 1; u <= n; ++u)
    dis[u] = INF;
  dis[s] = 0;
}

struct node {
  int d, u;
} pq[2 * M];
int size;

void push(int u) {
  pq[++size] = {dis[u], u};
  int i = size;
  while (i > 1 && pq[i].d < pq[i / 2].d)
    std::swap(pq[i], pq[i / 2]), i /= 2;
}

void pop() {
  pq[1] = pq[size], --size;
  int i = 1, j = 2;
  while (j <= size) {
    if (j < size && pq[j + 1].d < pq[j].d)
      ++j;
    if (pq[i].d <= pq[j].d)
      return;
    std::swap(pq[i], pq[j]);
    i = j, j *= 2;
  }
}

int vis[N];

void dijkstra(int s) {
  int u;
  for (u = cc_head[s]; u != 0; u = cc_nxt[u])
    if (dis[u] != INF)
      push(u);
  int i, v, w;
  while (size > 0) {
    u = pq[1].u;
    pop();
    if (vis[u] == 1)
      continue;
    vis[u] = 1;
    for (i = head[u]; i != 0; i = nxt[i]) {
      v = to[i], w = weight[i];
      if (dis[v] <= dis[u] + w)
        continue;
      dis[v] = dis[u] + w;
      push(v);
    }
  }
}

void topo(int s) {
  fr = 0, bk = 0;
  q[++bk] = s;
  int u, v, i;
  while (fr < bk) {
    s = q[++fr];
    dijkstra(s);
    for (u = cc_head[s]; u != 0; u = cc_nxt[u]) {
      for (i = p_head[u]; i != 0; i = p_nxt[i]) {
        v = p_to[i];
        dis[v] = std::min(dis[v], dis[u] + p_weight[i]);
        if (--in_deg[dsu[v]] == 0)
          q[++bk] = dsu[v];
      }
    }
  }
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);

  int n, m, p, s;
  std::cin >> n >> m >> p >> s;

  dsu_ini(n);

  int i, u, v, w;
  for (i = 1; i <= m; ++i) {
    std::cin >> u >> v >> w;
    unite(u, v);
    add(u, v, w);
    add(v, u, w);
  }

  for (u = 1; u <= n; ++u)
    cc_add(u);

  cnt = 0;
  for (i = 1; i <= p; ++i) {
    std::cin >> u >> v >> w;
    p_add(u, v, w);
  }

  get_in_deg(dsu[s]);

  dis_ini(n, s);

  topo(dsu[s]);

  for (u = 1; u <= n; ++u) {
    if (dis[u] == INF)
      std::cout << "NO PATH" << '\n';
    else
      std::cout << dis[u] << '\n';
  }

  return 0;
}