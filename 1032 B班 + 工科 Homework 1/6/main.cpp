#include <iostream>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int q;
    long long x, k;
    std::cin >> q;
    ++q;
    while (--q) {
        std::cin >> x;
        k = (int) cbrt(x + 0.5);
        std::cout << k * x - (k * (k - 1) >> 1) * ((k * (k + 3) + 4) >> 1) << '\n';
    }
    return 0;
}