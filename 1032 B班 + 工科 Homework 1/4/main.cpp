#include <iostream>
#include <cmath>

long long h[100005]; // Record data h before tag. 0_based
long long max[320]; // Record the maximum h in the interval. 0_based
long long multi_pow[7] = {2}; // Preprocess 2 ^ 2 ^ i. If max[i] < multi_pow[tag[i]] or tag[i] = 6, we know that
                              //for all h in the i-th interval, h = 1 after tag.
int tag[320]; // The i-th interval is processed as a whole for tag[i] times. 0_based
              //Ensure that tag[i] <= 6, i <= (n - 1) / sqrt_n. If max[i] < multi_pow[tag[i]], let tag[i] = 6.
int pos[100005]; // The i-th h is in the pos[i]-th interval. 0_based

constexpr long long multi_sqrt(long long x, int y) {
  ++y;
  while (--y && x != 1) {
    x = static_cast<long long>(sqrt(static_cast<double>(x)));
  }
  return x;
}

int main() {
  int i, j, n, m, k, l, r, pos_l, pos_r;
  for (i = 0; i < 6; ++i) multi_pow[i + 1] = multi_pow[i] * multi_pow[i];

  std::cin >> n;
  const int sqrt_n = static_cast<int>(sqrt(n));
  for (i = 0; i < n; ++i) pos[i] = i / sqrt_n;
  long long x, ans;
  for (i = 0; i < (n - 1) / sqrt_n; ++i) {
    for (j = 0; j < sqrt_n; ++j) {
      std::cin >> x;
      h[sqrt_n * i + j] = x;
      max[i] = std::max(max[i], x);
    } if (max[i] == 1) tag[i] = 6;
  }
  for (i = (n - 1) / sqrt_n * sqrt_n; i < n; ++i) {
    std::cin >> x;
    h[i] = x;
    max[(n - 1) / sqrt_n] = std::max(max[(n - 1) / sqrt_n], x);
  } if (max[(n - 1) / sqrt_n] == 1) tag[(n - 1) / sqrt_n] = 6;

  std::cin >> m;
  ++m;
  while (--m) {
    std::cin >> k >> l >> r;
    if (l > r) std::swap(l, r);
    pos_l = pos[--l], pos_r = pos[--r];

    if (k) {
      ans = 0;
      if (pos_l == pos_r) {
        if (tag[pos_l] < 6) {
          for (i = sqrt_n * pos_l; i < std::min(sqrt_n * (pos_r + 1), n); ++i) h[i] = multi_sqrt(h[i], tag[pos_l]);
          max[pos_l] = multi_sqrt(max[pos_l], tag[pos_l]);
          tag[pos_l] = 0;
          for (i = l; i <= r; ++i) ans += h[i];
          std::cout << ans << '\n';
        } else std::cout << r - l + 1 << '\n';
      }
      else {
        for (i = pos_l + 1; i < pos_r; ++i) {
          if (tag[i] < 6) {
            for (j = 0; j < sqrt_n; ++j) {
              h[sqrt_n * i + j] = multi_sqrt(h[sqrt_n * i + j], tag[i]);
              ans += h[sqrt_n * i + j];
            }
            max[i] = multi_sqrt(max[i], tag[i]);
            tag[i] = 0;
          } else ans += sqrt_n;
        }
        if (tag[pos_l] < 6) {
          for (i = sqrt_n * pos_l; i < sqrt_n * (pos_l + 1); ++i) h[i] = multi_sqrt(h[i], tag[pos_l]);
          max[pos_l] = multi_sqrt(max[pos_l], tag[pos_l]);
          tag[pos_l] = 0;
          for (i = sqrt_n * (pos_l + 1) - 1; i >= l; --i) ans += h[i];
        } else ans += sqrt_n * (pos_l + 1) - l;
        if (tag[pos_r] < 6) {
          for (i = std::min(n, sqrt_n * (pos_r + 1)) - 1; i >= sqrt_n * pos_r; --i) h[i] = multi_sqrt(h[i], tag[pos_r]);
          max[pos_r] = multi_sqrt(max[pos_r], tag[pos_r]);
          tag[pos_r] = 0;
          for (i = sqrt_n * pos_r; i <= r; ++i) ans += h[i];
        } else ans += r - sqrt_n * pos_r + 1;
        std::cout << ans << '\n';
      }
    }

    else {
      if (pos_l == pos_r) {
        if (tag[pos_l] < 6) {
          for (i = l; i <= r; ++i) h[i] = static_cast<long long>(sqrt(static_cast<double>(h[i])));
          max[pos_l] = 0;
          for (i = std::min(n, sqrt_n * (pos_r + 1)) - 1; i >= sqrt_n * pos_l; --i) max[pos_l] = std::max(max[pos_l], h[i]);
          if (max[pos_l] < multi_pow[tag[pos_l]]) tag[pos_l] = 6;
        }
      }
      else {
        for (i = pos_l + 1; i < pos_r; ++i) if (tag[i] < 6) ++tag[i];
        if (tag[pos_l] < 6) {
          for (i = sqrt_n * (pos_l + 1) - 1; i >= l; --i) h[i] = static_cast<long long>(sqrt(static_cast<double>(h[i])));
          max[pos_l] = 0;
          for (i = sqrt_n * (pos_l + 1) - 1; i >= sqrt_n * pos_l; --i) max[pos_l] = std::max(max[pos_l], h[i]);
          if (max[pos_l] < multi_pow[tag[pos_l]]) tag[pos_l] = 6;
        }
        if (tag[pos_r] < 6) {
          for (i = sqrt_n * pos_r; i <= r; ++i) h[i] = static_cast<long long>(sqrt(static_cast<double>(h[i])));
          max[pos_r] = 0;
          for (i = std::min(n, sqrt_n * (pos_r + 1)) - 1; i >= sqrt_n * pos_r; --i) max[pos_r] = std::max(max[pos_r], h[i]);
          if (max[pos_r] < multi_pow[tag[pos_r]]) tag[pos_r] = 6;
        }
      }
    }
  }
  return 0;
}