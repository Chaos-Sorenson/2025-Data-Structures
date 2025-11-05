#include <iostream>

struct Node {
  double sum, sum2, lazy;
};

constexpr int MAXN = 1e5 + 5;
Node tree[MAXN << 2];
double a[MAXN];
int n, m, x, y;
double k;

void up(int rt) {
  tree[rt].sum = tree[rt << 1].sum + tree[rt << 1 | 1].sum;
  tree[rt].sum2 = tree[rt << 1].sum2 + tree[rt << 1 | 1].sum2;
}

void down(int rt, int l, int r) {
  if (tree[rt].lazy == 0) return;
  int mid = l + r >> 1;
  double lazy = tree[rt].lazy;

  tree[rt << 1].lazy += lazy;
  tree[rt << 1].sum2 += 2 * lazy * tree[rt << 1].sum + (mid - l + 1) * lazy * lazy;
  tree[rt << 1].sum += (mid - l + 1) * lazy;

  tree[rt << 1 | 1].lazy += lazy;
  tree[rt << 1 | 1].sum2 += 2 * lazy * tree[rt << 1 | 1].sum + (r - mid) * lazy * lazy;
  tree[rt << 1 | 1].sum += (r - mid) * lazy;

  tree[rt].lazy = 0;
}

void build(int rt, int l, int r) {
  if (l == r) {
    tree[rt].sum = a[l];
    tree[rt].sum2 = a[l] * a[l];
    return;
  }
  int mid = l + r >> 1;
  build(rt << 1, l, mid);
  build(rt << 1 | 1, mid + 1, r);
  up(rt);
}

void update(int rt, int l, int r) {
  if (x <= l && r <= y) {
    tree[rt].lazy += k;
    tree[rt].sum2 += 2 * k * tree[rt].sum + (r - l + 1) * k * k;
    tree[rt].sum += (r - l + 1) * k;
    return;
  }
  down(rt, l, r);
  int mid = l + r >> 1;
  if (x <= mid) update(rt << 1, l, mid);
  if (y > mid) update(rt << 1 | 1, mid + 1, r);
  up(rt);
}

double query_sum(int rt, int l, int r) {
  if (x <= l && r <= y) return tree[rt].sum;
  down(rt, l, r);
  int mid = l + r >> 1;
  double res = 0;
  if (x <= mid) res += query_sum(rt << 1, l, mid);
  if (y > mid) res += query_sum(rt << 1 | 1, mid + 1, r);
  return res;
}

double query_sum2(int rt, int l, int r) {
  if (x <= l && r <= y) return tree[rt].sum2;
  down(rt, l, r);
  int mid = l + r >> 1;
  double res = 0;
  if (x <= mid) res += query_sum2(rt << 1, l, mid);
  if (y > mid) res += query_sum2(rt << 1 | 1, mid + 1, r);
  return res;
}

void show(int rt, int l,int r) {
  using namespace std;
  cout << l << ' ' << r << ' ' << tree[rt].sum << ' ' << tree[rt].sum2 << ' ' << tree[rt].lazy << '\n';
  if (l == r) return;
  show (rt << 1, l, l + r >> 1), show(rt << 1 | 1, l + r + 2 >> 1, r);
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::cin >> n >> m;
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];
  build(1, 1, n);
  while (m--) {
    int op;
    std::cin >> op;
    if (op == 1) {
      std::cin >> x >> y >> k;
      update(1, 1, n);
    }
    else if (op == 2) {
      std::cin >> x >> y;
      double avg = 100 * query_sum(1, 1, n) / (y - x + 1);
      std::cout << (int)(avg) << '\n';
    }
    else {
      std::cin >> x >> y;
      double avg = 10 * query_sum(1, 1, n) / (y - x + 1);
      double avg2 = 100 * query_sum2(1, 1, n) / (y - x + 1);
      std::cout << (int)(avg2 - avg * avg) << '\n';
    }
  }
  return 0;
}