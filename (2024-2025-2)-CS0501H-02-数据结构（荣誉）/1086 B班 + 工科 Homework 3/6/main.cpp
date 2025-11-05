#include <iostream>

int n, m, i, j, a, b, c, d, e, g, l2[100001], s1[100002], v[100001], st[17][100001], f[50001];

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n >> m >> a;
  for (i = 2; i <= n; ++i) {
    std::cin >> b;
    if (a < b) f[++e] = i;
    s1[i] = c += a,
    v[i] = d += 1 - a - b,
    st[0][i] = i,
    l2[i] = l2[i >> 1] + 1, a = b;
  }
  s1[n + 1] = c + a, st[0][1] = 1;

  g = l2[n];
  for (; j < g; ++j) {
    a = 1 << j, b = n - a;
    for (i = 1; i <= b; ++i)
      c = st[j][i], d = st[j][i + a],
      st[j + 1][i] = v[c] > v[d] ? c : d;
  }

  ++m; while (--m) {
    std::cin >> a >> i >> j;
    if (a == 1) {
      a = l2[j - i + 1],
      b = st[a][i], c = st[a][j + 1 - (1 << a)],
      a = v[b] > v[c] ? b : c;
      std::cout << a - i + s1[i] - s1[a] - s1[a + 1] + s1[j + 1] + 1 << '\n';
    }
    else {
      if (f[e] <= i) {
        std::cout << "1\n";
        continue;
      }
      a = 0, b = e;
      while (b - a > 1) {
        c = a + b >> 1;
        if (f[c] > i) b = c;
        else a = c;
      }
      std::cout << (f[b] <= j ? "2\n" : "1\n");
    }
  }
}