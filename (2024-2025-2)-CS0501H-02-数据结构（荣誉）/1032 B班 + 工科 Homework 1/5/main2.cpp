#include <iostream>

constexpr int S = 1000;
int n, q, Q, R, h[S][S], H[S][S], tag[S];

void heap_sort(const int p) {
  if (p == 0 || p == Q) return;
  int i, j, k, *arr = H[p];
  for (i = 0; i < S; ++i) arr[i] = h[p][i];
  for (i = (S >> 1) - 1; i >= 0 ; --i) {
    j = i;
    while ((k = (j << 1) + 1) < S) {
      if (k + 1 < S && arr[k] < arr[k + 1]) ++k;
      if (arr[j] >= arr[k]) break;
      std::swap(arr[j], arr[k]);
      j = k;
    }
  }
  for (i = S - 1; i > 0; --i) {
    std::swap(arr[0], arr[i]);
    j = 0;
    while ((k = (j << 1) + 1) < i) {
      if (k + 1 < i && arr[k] < arr[k + 1]) ++k;
      if (arr[j] >= arr[k]) break;
      std::swap(arr[j], arr[k]);
      j = k;
    }
  }
}

int binary_count(const int p, const int x) {
  const int *arr = H[p];
  if (arr[0] >= x) return S;
  if (arr[S - 1] < x) return 0;
  int lh = 0, rh = S - 1;
  while (lh + 1 < rh) {
    if (const int mid = lh + rh >> 1; arr[mid] < x) lh = mid;
    else rh = mid;
  }
  return S - rh;
}

void update(const int l, const int r, const int x) {
  const int bl = l / S, br = r / S;
  for (int i = std::min(r - bl * S, S - 1); i >= l % S; --i) h[bl][i] += x;
  heap_sort(bl);
  if (bl == br) return;
  for (int i = r % S; i >= 0; --i) h[br][i] += x;
  heap_sort(br);
  for (int i = bl + 1; i < br; ++i) tag[i] += x;
}

void query(const int l, const int r, int x) {
  const int bl = l / S, br = r / S;
  int cnt = 0;
  x -= tag[bl];
  for (int i = std::min(r - bl * S, S - 1); i >= l % S; --i) cnt += h[bl][i] >= x;
  if (bl == br) {
    std::cout << cnt << '\n';
    return;
  }
  x += tag[bl] - tag[br];
  for (int i = r % S; i >= 0; --i) cnt += h[br][i] >= x;
  x += tag[br];
  for (int i = bl + 1; i < br; ++i) cnt += binary_count(i, x - tag[i]);
  std::cout << cnt << '\n';
}

int main() {
  std::cin >> n >> q;
  Q = (n - 1) / S, R = (n - 1) % S;
  for (int i = 0; i < n; ++i) std::cin >> h[i / S][i % S];
  for (int i = 1; i < Q; ++i) heap_sort(i);
  char c;
  int l, r, x;
  ++q;
  while (--q) {
    std::cin >> c >> l >> r >> x;
    if (c == 'M') update(l - 1 , r - 1, x);
    else if (c == 'A') query(l - 1, r - 1, x);
  }
  return 0;
}