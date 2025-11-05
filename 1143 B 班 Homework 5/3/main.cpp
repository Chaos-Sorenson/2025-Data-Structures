#include <iostream>
#include <climits>

constexpr int M = 105, N = 1005;
int board[M][M], dist[M][M];

struct Node {
  int x, y;
  Node *next;
} *buc[3 * N];

int qx[N], qy[N];
int front, back;

int m, n;

void check(int x, int y, int c, int d) {
  if (x < 1 || x > m || y < 1 || y > m ||
    board[x][y] != c || dist[x][y] <= d)
    return;

  ++back;
  qx[back] = x, qy[back] = y;
  buc[d] = new Node({x, y, buc[d]});
  dist[x][y] = d;
}

void getClosure(int x, int y, int c, int d) {
  if (dist[x][y] < d)
    return;
  front = 0, back = 1;
  qx[1] = x, qy[1] = y;

  while(front < back) {
    ++front;
    x = qx[front], y = qy[front];
    check(x - 1, y, c, d);
    check(x + 1, y, c, d);
    check(x, y - 1, c, d);
    check(x, y + 1, c, d);
  }
}

void checkAndGetCLosure(int x, int y, int c, int d) {
  if (x < 1 || x > m || y < 1 || y > m ||
    board[x][y] != c || dist[x][y] <= d)
    return;
  dist[x][y] = d;
  buc[d] = new Node({x, y, buc[d]});
  getClosure(x, y, c, d);
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::cin >> m >> n;

  int x, y;
  for (x = 1; x <= m; ++x)
    for (y = 1; y <= m; ++y)
      board[x][y] = -1;

  int i, c;
  for (i = 1; i <= n; ++i) {
    std::cin >> x >> y >> c;
    board[x][y] = c;
    dist[x][y] = INT_MAX;
  }

  dist[1][1] = 0;
  buc[0] = new Node({1, 1, 0});
  getClosure(1, 1, board[1][1], 0);

  int d;
  Node *ptr;
  bool flag_u, flag_d, flag_l, flag_r;

  for (d = 1; d <= 3 * n; ++d) {

    for (ptr = buc[d - 1]; ptr != 0; ptr = ptr->next) {
      x = ptr->x, y = ptr->y, c = 1 - board[x][y];
      if (dist[x][y] < d - 1)
        continue;

      checkAndGetCLosure(x - 1, y, c, d);
      checkAndGetCLosure(x + 1, y, c, d);
      checkAndGetCLosure(x, y - 1, c, d);
      checkAndGetCLosure(x, y + 1, c, d);
    }

    if (d == 1)
      continue;

    for (ptr = buc[d - 2]; ptr != 0; ptr = ptr->next) {
      x = ptr->x, y = ptr->y, c = board[x][y];
      if (dist[x][y] < d - 2)
        continue;

      flag_u = x > 1 && board[x - 1][y] == -1;
      flag_d = x < m && board[x + 1][y] == -1;
      flag_l = y > 1 && board[x][y - 1] == -1;
      flag_r = y < m && board[x][y + 1] == -1;

      if (flag_u)
        checkAndGetCLosure(x - 2, y, c, d);
      if (flag_d)
        checkAndGetCLosure(x + 2, y, c, d);
      if (flag_l)
        checkAndGetCLosure(x, y - 2, c, d);
      if (flag_r)
        checkAndGetCLosure(x, y + 2, c, d);
      if (flag_u && flag_l)
        checkAndGetCLosure(x - 1, y - 1, c, d);
      if (flag_u && flag_r)
        checkAndGetCLosure(x - 1, y + 1, c, d);
      if (flag_d && flag_l)
        checkAndGetCLosure(x + 1, y - 1, c, d);
      if (flag_d && flag_r)
        checkAndGetCLosure(x + 1, y + 1, c, d);
    }

    if (d == 2)
      continue;

    for(ptr = buc[d - 3]; ptr != 0; ptr = ptr->next) {
      x = ptr->x, y = ptr->y, c = 1 - board[x][y];
      if (dist[x][y] < d - 3)
        continue;

      flag_u = x > 1 && board[x - 1][y] == -1;
      flag_d = x < m && board[x + 1][y] == -1;
      flag_l = y > 1 && board[x][y - 1] == -1;
      flag_r = y < m && board[x][y + 1] == -1;

      if (flag_u)
        checkAndGetCLosure(x - 2, y, c, d);
      if (flag_d)
        checkAndGetCLosure(x + 2, y, c, d);
      if (flag_l)
        checkAndGetCLosure(x, y - 2, c, d);
      if (flag_r)
        checkAndGetCLosure(x, y + 2, c, d);
      if (flag_u && flag_l)
        checkAndGetCLosure(x - 1, y - 1, c, d);
      if (flag_u && flag_r)
        checkAndGetCLosure(x - 1, y + 1, c, d);
      if (flag_d && flag_l)
        checkAndGetCLosure(x + 1, y - 1, c, d);
      if (flag_d && flag_r)
        checkAndGetCLosure(x + 1, y + 1, c, d);
    }
  }

  if (board[m][m] != -1) {
    std::cout << (dist[m][m] == INT_MAX ? -1 : dist[m][m]);
    return 0;
  }
  int ans = INT_MAX;
  if (board[m - 1][m] != -1 && dist[m - 1][m] != INT_MAX)
    ans = dist[m - 1][m] + 2;
  if (board[m][m - 1] != -1 && dist[m][m - 1] != INT_MAX)
    ans = std::min(ans, dist[m][m - 1] + 2);
  std::cout << (ans == INT_MAX ? -1 : ans);
}