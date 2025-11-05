#include <iostream>

constexpr int MAX = 200000;
int N, M, L, R, i, j, ai, fi, x, l, r, m, log_2[MAX + 1], a[MAX], f[MAX], st[19][MAX];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> N >> M >> a[0];

  for (i = 2; i <= N; ++i)
    log_2[i] = log_2[i >> 1] + 1;

  for (i = 1; i < N; ++i) {
    std::cin >> ai; a[i] = ai;
    for (j = i - 1, fi = f[i - 1]; j >= fi; --j)
      if (a[j] == ai) break;
    f[i] = j + 1, st[0][i] = i - j;
  }

  for (j = 0, x = log_2[N]; j < x; ++j)
    for (i = 0; i < N - (1 << j); ++i)
      st[j + 1][i] = std::max(st[j][i], st[j][i + (1 << j)]);

  ++M; while (--M) {
    std::cin >> L >> R;
    if (f[R] <= L) {
      std::cout << R - L + 1 << '\n';
      continue;
    }
    l = L, r = R;
    while (m = l + r >> 1, r - l > 1)
      if (f[m] > L) r = m;
      else l = m;
    x = log_2[R - r + 1];
    std::cout << std::max(r - L, std::max(st[x][r], st[x][R + 1 - (1 << x)])) << '\n';
  }
  return 0;
}