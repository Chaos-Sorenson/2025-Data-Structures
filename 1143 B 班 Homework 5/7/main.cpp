#include <iostream>

constexpr int N = 1e5 + 10;
int edge_cnt, head[N], to[2 * N], next[2 * N], weight[2 * N];
int total = 1, dis[N], ch[N << 5][2], ans, res;

void add(int u, int v, int w) {
  to[++edge_cnt] = v;
  next[edge_cnt] = head[u];
  head[u] = edge_cnt;
  weight[edge_cnt] = w;
}

int i, c, rt;
void insert(int x) {
  for (i = 30, rt = 1; i >= 0; --i) {
    c = (x >> i) % 2;
    if (ch[rt][c] == 0)
      ch[rt][c] = ++total;
    rt = ch[rt][c];
  }
}

void get(int x) {
  for (i = 30, rt = 1, res = 0; i >= 0; --i) {
    c = (x >> i) % 2;
    if (ch[rt][1 - c] != 0) {
      rt = ch[rt][1 - c];
      res += (1 << i);
    }
    else
      rt = ch[rt][c];
  }
  ans = std::max(ans, res);
}

void dfs(int u, int fa) {
  insert(dis[u]);
  get(dis[u]);

  int v;
  for (int i = head[u]; i != 0; i = next[i]) {
    if ((v = to[i]) == fa)
      continue;

    dis[v] = dis[u] ^ weight[i];
    dfs(v, u);
  }
}

int main() {
  std::cin.tie(0)->sync_with_stdio(0);

  int n;
  std::cin >> n;

  int i, u, v, w;
  for (i = 1; i < n; ++i) {
    std::cin >> u >> v >> w;
    add(u, v, w);
    add(v, u, w);
  }

  dfs(1, 0);

  std::cout << ans;

  return 0;
}