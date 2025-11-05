#include <iostream>

constexpr int N = 100001;
int n, i, b[N], c[N], query(int), l, r, m;
void search(int), update();

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n;
  for (i = 1; i <= n; ++i) {
    std::cin >> b[i];
    c[i] = i & -i;
  }

  for (i = n; i; --i)
    search(b[i] + 1), update();

  for (i = 1; i <= n; ++i)
    std::cout << b[i] << ' ';
  return 0;
}

int query(int x) {
  int r = 0;
  while (x)
    r += c[x],
    x -= x & -x;
  return r;
}

void update() {
  while (r <= n)
    --c[r], r += r & -r;
}

void search(const int x) {
  l = 0, r = n;
  while (r - l > 1)
    if (m = l + r >> 1; query(m) < x) l = m;
    else r = m;
  b[i] = r;
}