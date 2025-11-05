#include <iostream>

int n, q, i, j;
long long MOD, k, a[100001];

struct treeNode {
  int l, r;
  long long sum, tag, tag2;
} segTree[400000];

void buildTree(int, int, int), down(int), update(int), update2(int);
long long query(int);

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::cin >> n >> q >> MOD;
  for (i = 1; i <= n; ++i)
    std::cin >> a[i];
  buildTree(1, 1, n);

  // std::cout << '\n';
  // for (i = 1; i < n << 1; ++i) {
  //   auto [l, r, s, t, t2] = segTree[i];
  //   std::cout << l << ' ' << r << ' ' << s << '\n';
  // }
  // std::cout << '\n';

  ++q;
  while (--q) {
    std::cin >> k;
    switch (k) {
      case 1:
        std::cin >> i >> j >> k;
        update2(1);
        break;
      case 2:
        std::cin >> i >> j >> k;
        update(1);
        break;
      case 3:
        std::cin >> i >> j;
        std::cout << query(1) << '\n';
        break;
      default:
        break;
    }

    // std::cout << '\n';
    // for (i = 1; i < n << 1; ++i) {
    //   auto [l, r, s, t, t2] = segTree[i];
    //   std::cout << l << ' ' << r << ' ' << s << ' ' << t << ' ' << t2 << '\n';
    // }
    // std::cout << '\n';

  }
}

void buildTree(const int root, const int l, const int r) {
  auto &[cl, cr, cs, ct, ct2] = segTree[root];
  cl = l, cr = r, ct2 = 1;
  if (l == r) {
    cs = a[l];
    return;
  }
  const auto m = l + r >> 1;
  buildTree(root << 1, l, m), buildTree(root << 1 | 1, m + 1, r);
  cs = segTree[root << 1].sum + segTree[root << 1 | 1].sum;
}

void down(const int root) {
  auto &ct = segTree[root].tag, &ct2 = segTree[root].tag2;
  auto &[ll, lr, ls, lt, lt2] = segTree[root << 1];
  ls = (ls * ct2 + (lr - ll + 1) * ct) % MOD;
  lt2 = lt2 * ct2 % MOD, lt = (lt * ct2 + ct) % MOD;
  auto &[rl, rr, rs, rt, rt2] = segTree[root << 1 | 1];
  rs = (rs * ct2 + (rr - rl + 1) * ct) % MOD;
  rt2 = rt2 * ct2 % MOD, rt = (rt * ct2 + ct) % MOD;
  ct = 0, ct2 = 1;
}

void update(const int root) {
  auto &[cl, cr, cs, ct, ct2] = segTree[root];
  if (cl >= i && cr <= j) {
    cs = (cs + (cr - cl + 1) * k) % MOD, ct = (ct + k) % MOD;
    return;
  }
  down(root);
  const auto m = cl + cr >> 1;
  if (i <= m)
    update(root << 1);
  if (j > m)
    update(root << 1 | 1);
  cs = (segTree[root << 1].sum + segTree[root << 1 | 1].sum) % MOD;
}

void update2(const int root) {
  auto &[cl, cr, cs, ct, ct2] = segTree[root];
  if (cl >= i && cr <= j) {
    cs = cs * k % MOD, ct2 = ct2 * k % MOD, ct = ct * k % MOD;
    return;
  }
  down(root);
  const auto m = cl + cr >> 1;
  if (i <= m)
    update2(root << 1);
  if (j > m)
    update2(root << 1 | 1);
  cs = (segTree[root << 1].sum + segTree[root << 1 | 1].sum) % MOD;
}

long long query(const int root) {
  auto [cl, cr, cs, ct, ct2] = segTree[root];
  if (cl >= i && cr <= j)
    return cs % MOD;
  down(root);
  const auto m = cl + cr >> 1;
  if (j <= m)
    return query(root << 1);
  if (i > m)
    return query(root << 1 | 1);
  return (query(root << 1) + query(root << 1 | 1)) % MOD;
}