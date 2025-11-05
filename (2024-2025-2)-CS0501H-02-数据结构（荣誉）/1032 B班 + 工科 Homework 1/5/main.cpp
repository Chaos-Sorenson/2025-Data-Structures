#include <iostream>

int h[1000005], tag[4000020], min[4000020], max[4000020], lh[4000020], rh[4000020], l, r, x;

void build_tree(const int pos, const int ll, const int rr) {
  lh[pos] = ll, rh[pos] = rr;
  if (ll == rr) {
    min[pos] = max[pos] = h[ll];
    return;
  }
  const int m = (ll + rr) >> 1, child = pos << 1;
  build_tree(child, ll, m), build_tree(child + 1, m + 1, rr);
  min[pos] = std::min(min[child], min[child + 1]), max[pos] = std::max(max[child], max[child + 1]);
}

void update(const int pos) {
  if (l > r || r < lh[pos] || rh[pos] < l) return;
  if (l <= lh[pos] && rh[pos] <= r) {
    min[pos] += x, max[pos] += x, tag[pos] += x;
    return;
  }
  const int t = tag[pos], child = pos << 1, m = rh[child];
  if (t > 0) min[child] += t, max[child] += t, tag[child] += t, min[child + 1] += t, max[child + 1] += t, tag[child + 1] += t, tag[pos] = 0;
  if (l <= m) update(child);
  if (r > m) update(child + 1);
  min[pos] = std::min(min[child], min[child + 1]), max[pos] = std::max(max[child], max[child + 1]);
}

int count(const int pos) {
  if (x > max[pos] || l > r || r < lh[pos] || rh[pos] < l) return 0;
  if (l <= lh[pos] && rh[pos] <= r) {
    if (x <= min[pos]) return rh[pos] - lh[pos] + 1;
    if (lh[pos] == rh[pos]) return 0;
  }
  const int t = tag[pos], child = pos << 1, m = rh[child];
  if (t > 0) min[child] += t, max[child] += t, tag[child] += t, min[child + 1] += t, max[child + 1] += t, tag[child + 1] += t, tag[pos] = 0;
  int ans = 0;
  if (l <= m) ans += count(child);
  if (r > m) ans += count(child + 1);
  return ans;
}

int main() {
  int n, q;
  std::cin >> n >> q;
  for (int i = 0; i < n; ++i) std::cin >> h[i];
  build_tree(1, 0, n - 1);
  char c;
  ++q;
  while (--q) {
    std::cin >> c >> l >> r >> x;
    --l, --r;
    if (l > r) std::swap(l, r);
    if (c == 'M') update(1);
    else std::cout << count(1) << '\n';
  }
  return 0;
}