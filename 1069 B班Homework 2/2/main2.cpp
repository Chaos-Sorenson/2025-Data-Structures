#include <iostream>

int x, ch;
bool f;
inline int read() {
  x = 0, ch = getchar(),
  f = ch == 45;
  if (f) ch = getchar();
  while (ch > 47)
    x = 10 * x + ch - 48,
    ch = getchar();
  return f ? -x : x;
}

constexpr int N = 10000000;

int n, m, i, pr[N + 2], ne[N + 1];
long long s[N + 1], a, si;

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  n = read(), m = read();
  for (i = 0; i < n; ++i)
    si = s[i + 1] = si + read();

  a = s[n] - s[n - 1];
  pr[n + 1] = ne[0] = n,
  ne[n] = n + 1;

  for (i = n - 1; i > 0; --i) {
    if (ne[0] >= i + m)
      ne[0] = ne[ne[0]],
      pr[ne[0]] = 0;

    si = s[i];
    while (pr[n + 1] && s[pr[n + 1]] <= si)
      pr[n + 1] = pr[pr[n + 1]];

    pr[i] = pr[n + 1],
    ne[i] = n + 1,
    ne[pr[i]] = pr[n + 1] = i,
    a = std::max(a, s[ne[0]] - s[i - 1]);
  }

  std::cout << a;
  return 0;
}