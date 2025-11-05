#include <iostream>

int n, m, i, j;
long long k, a[100001];

struct treeNode {
  int l, r;
  long long sum, tag;
} segTree[400000];

void buildTree(int, int, int), down(int), update(int);
long long query(int);

int main() {
  std::cin >> n >> m;
  for (i = 1; i <= n; ++i)
    std::cin >> a[i];
  buildTree(1, 1, n);

  // std::cout << '\n';
  // for (i = 1; i < n << 1; ++i) {
  //   auto [l, r, s, t] = segTree[i];
  //   std::cout << l << ' ' << r << ' ' << s << '\n';
  // }

  ++m;
  while (--m) {
    std::cin >> k;
    switch (k) {
      case 1:
        std::cin >> i >> j >> k;
        update(1);

        // std::cout << '\n';
        // for (i = 1; i < n << 1; ++i) {
        //   auto [l, r, s, t] = segTree[i];
        //   std::cout << l << ' ' << r << ' ' << s << ' ' << t << '\n';
        // }

        break;
      case 2:
        std::cin >> i >> j;
        std::cout << query(1) << '\n';
        break;
      default:
        break;
    }
  }
}

void buildTree(const int root, const int l, const int r) {
  auto &[cl, cr, cs, ct] = segTree[root];
  cl = l, cr = r;
  if (l == r) {
    cs = a[l];
    return;
  }
  const auto m = l + r >> 1;
  buildTree(root << 1, l, m), buildTree(root << 1 | 1, m + 1, r);
  cs = segTree[root << 1].sum + segTree[root << 1 | 1].sum;
}

void down(const int root) {
  auto &ct = segTree[root].tag;
  auto &[ll, lr, ls, lt] = segTree[root << 1];
  auto &[rl, rr, rs, rt] = segTree[root << 1 | 1];
  ls += (lr - ll + 1) * ct, lt += ct, rs += (rr - rl + 1) * ct, rt += ct, ct = 0;
}
void update(const int root) {
  auto &[cl, cr, cs, ct] = segTree[root];
  if (cl >= i && cr <= j) {
    cs += (cr - cl + 1) * k, ct += k;
    return;
  }
  down(root);
  const auto m = cl + cr >> 1;
  if (i <= m)
    update(root << 1);
  if (j > m)
    update(root << 1 | 1);
  cs = segTree[root << 1].sum + segTree[root << 1 | 1].sum;
}

long long query(const int root) {
  auto [cl, cr, cs, ct] = segTree[root];
  if (cl >= i && cr <= j)
    return cs;
  down(root);
  const auto m = cl + cr >> 1;
  if (j <= m)
    return query(root << 1);
  if (i > m)
    return query(root << 1 | 1);
  return query(root << 1) + query(root << 1 | 1);
}