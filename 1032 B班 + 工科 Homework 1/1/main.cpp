#include <iostream>
#include <cmath>

int sum[8000] = {};
bool tag[8000] = {}, facing[50000050] = {};
int main() {
  int n, m, c, a, b, lh, rh, ans, ansl, ansr;
  std::cin >> n >> m;
  int sqrtn = std::ceil(std::sqrt(n));
  ++m;
  while (--m) {
    std::cin >> c >> a >> b;
    lh = --a / sqrtn, rh = --b / sqrtn, ans = ansl = ansr = 0;;
    if (c) {
      if (lh < rh) {
        for (int i = lh + 1; i < rh; ++i) ans += tag[i] ? sqrtn - sum[i] : sum[i];
        for (int i = (lh + 1) * sqrtn - 1; i >= a; --i) ansl += facing[i];
        for (int i = rh * sqrtn; i <= b; ++i) ansr += facing[i];
        std::cout << ans + (tag[lh] ? (lh + 1) * sqrtn - a - ansl : ansl) + (tag[rh] ? b - rh * sqrtn + 1 - ansr : ansr) << '\n';
      } else {
        for (int i = a; i <= b; ++i) ans += facing[i];
        std::cout << (tag[lh] ? b - a + 1 - ans : ans) << '\n';
      }
    } else {
      if (lh < rh) {
        for (int i = lh + 1; i < rh; ++i) tag[i] = !tag[i];
        for (int i = (lh + 1) * sqrtn - 1; i >= a; --i) {
          facing[i] = !facing[i];
          if (facing[i]) ++sum[lh];
          else --sum[lh];
        } for (int i = rh * sqrtn; i <= b; ++i) {
          facing[i] = !facing[i];
          if (facing[i]) ++sum[rh];
          else --sum[rh];
        }
      } else for (int i = a; i <= b; ++i) {
        facing[i] = !facing[i];
        if (facing[i]) ++sum[lh];
        else --sum[lh];
      }
    }
  }
  return 0;
}