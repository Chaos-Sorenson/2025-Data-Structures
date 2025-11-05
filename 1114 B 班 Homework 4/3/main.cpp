#include <iostream>

struct Node {
  int lmax, rmax, max;
  bool full, empty;
};

constexpr int MAXN = 5e4 + 5;
int N, M, op, X, D;
Node tree[MAXN << 2];

void up(int rt, int l, int r) {
  auto [llm, lrm, lm, lf, le] = tree[rt << 1];
  auto [rlm, rrm, rm, rf, re] = tree[rt << 1 | 1];
  auto mid = l + r >> 1, llen = mid - l + 1, rlen = r - mid;

  tree[rt] = {llm + (llm == llen) * rlm, rrm + (rrm == rlen) * lrm, std::max(std::max(lm, rm), lrm + rlm), 0, 0};
}

void down(int rt, int l, int r) {
  if (!tree[rt].full && !tree[rt].empty) return;

  if (tree[rt].full)
    tree[rt << 1] = tree[rt << 1 | 1] = {0, 0, 0, 1, 0};

  if (tree[rt].empty) {
    auto mid = l + r >> 1, llen = mid - l + 1, rlen = r - mid;
    tree[rt << 1] = {llen, llen, llen, 0, 1};
    tree[rt << 1 | 1] = {rlen, rlen, rlen, 0, 1};
  }

  tree[rt].full = tree[rt].empty = 0;
}

void build(int rt, int l, int r) {
  int len = r - l + 1;
  tree[rt] = {len, len, len, 0, 1};
  if (r == l) return;
  int mid = l + r >> 1;
  build(rt << 1, l, mid), build(rt << 1 | 1, mid + 1, r);
}

int query(int rt, int l, int r) {
  if (tree[rt].max < D) return 0;
  if (tree[rt].lmax >= D) return l;

  down(rt, l, r);
  auto mid = l + r >> 1;
  if (tree[rt << 1].max >= D) return query(rt << 1, l, mid);
  if (tree[rt << 1].rmax + tree[rt << 1 | 1].lmax >= D) return mid - tree[rt << 1].rmax + 1;
  return query(rt << 1 | 1, mid + 1, r);
}

void fill(int rt, int l, int r) {
  if (X <= l && r < X + D) {
    tree[rt] = {0, 0, 0, 1, 0};
    return;
  }

  down(rt, l, r);
  auto mid = l + r >> 1;
  if (X <= mid) fill(rt << 1, l, mid);
  if (X + D - 1 > mid) fill(rt << 1 | 1, mid + 1, r);
  up(rt, l, r);
}

void clear(int rt, int l, int r) {
  if (X <= l && r < X + D) {
    auto len = r - l + 1;
    tree[rt] = {len, len, len, 0, 1};
    return;
  }

  down(rt, l, r);
  auto mid = l + r >> 1;
  if (X <= mid) clear(rt << 1, l, mid);
  if (X + D - 1 > mid) clear(rt << 1 | 1, mid + 1, r);
  up(rt, l, r);
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  std::cout.tie(0);

  std::cin >> N >> M;

//   build(1, 1, N);
  tree[1] = {N, N, N, 0, 1};
  
  while (M--) {
    std::cin >> op;
    if (op == 1) {
      std::cin >> D;
      X = query(1, 1, N);
      if (X != 0) fill(1, 1, N);
      std::cout << X << '\n';
    }
    else {
      std::cin >> X >> D;
      if (D == 0)
        continue;
      clear(1, 1, N);
    }
  }
}