#include <iostream>

constexpr int M = 100000;
int N, D, i, x[M + 1], y[M + 1], ne[M + 1], pr[M + 2],
W = 100000001, xl, yi;

void down(int i, const int n) {
  i <<= 1;
  while (i <= n) {
    if (i < n && x[i] < x[i + 1]) ++i;
    if (x[i] <= x[i >> 1]) break;
    std::swap(x[i], x[i >> 1]);
    std::swap(y[i], y[i >> 1]);
    i <<= 1;
  }
}

int main() {
  std::cin >> N >> D;
  for (i = 1; i <= N; ++i)
    std::cin >> x[i] >> y[i];

  for (i = N >> 1; i > 0; --i)
    down(i, N);
  for (i = N; i > 1; --i)
    std::swap(x[1], x[i]),
    std::swap(y[1], y[i]),
    down(1, i - 1);

  pr[N + 1] = ne[0] = 1, ne[1] = N + 1;

  for (i = 2; i <= N; ++i) {
    xl = x[i] - W;
    while (ne[0] != N + 1 && x[ne[0]] <= xl)
      ne[0] = ne[ne[0]];
    pr[ne[0]] = 0;

    yi = y[i];
    while (pr[N + 1] && y[pr[N + 1]] >= yi)
      pr[N + 1] = pr[pr[N + 1]];

    pr[i] = pr[N + 1],
    ne[i] = N + 1,
    ne[pr[i]] = pr[N + 1] = i;

    if (yi - y[ne[0]] >= D)
      W = x[i] - x[ne[0]];
  }

  pr[N + 1] = ne[0] = 1, ne[1] = N + 1;

  for (i = 2; i <= N; ++i) {
    xl = x[i] - W;
    while (ne[0] != N + 1 && x[ne[0]] <= xl)
      ne[0] = ne[ne[0]];
    pr[ne[0]] = 0;

    yi = y[i];
    while (pr[N + 1] && y[pr[N + 1]] <= yi)
      pr[N + 1] = pr[pr[N + 1]];

    pr[i] = pr[N + 1],
    ne[i] = N + 1,
    ne[pr[i]] = pr[N + 1] = i;

    if (y[ne[0]] - yi >= D)
      W = x[i] - x[ne[0]];
  }

  std::cout << (W == 100000001 ? -1 : W);
  return 0;
}