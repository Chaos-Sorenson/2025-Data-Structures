#include <iostream>
#include <string>


int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::string order, s, ans;
  char ch;
  int t, n, pos = 0;
  std::cin >> t;
  ++t;
  while (--t) {
    std::cin >> order;
    if (order =="Anchor") {
      std::cin >> pos;
    } else if (order == "Summon") {
      s.clear();
      std::cin >> n;
      ++n;
      while (--n) {
        std::cin.get(ch);
        while (ch == '\n') std::cin.get(ch);
        s.push_back(ch);
      } ans.insert(ans.begin() + pos, s.begin(), s.end());
    } else if (order == "Annihilate") {
      std::cin >> n;
      ans.erase(ans.begin() + pos, ans.begin() + pos + n);
    } else if (order == "Manifest") {
      std::cin >> n;
      for (int i = 0; i < n; ++i) std::cout << ans[pos + i];
      std::cout << '\n';
    } else if (order == "Rewind") {
      --pos;
    } else if (order == "Surge") {
      ++pos;
    }
  }
  return 0;
}