#include <iostream>

constexpr int M = 100001;
long long a[M], b[M], s, v;
int N, Q, i, x, y, r, c;

inline int read() {
  r = 0;
  while ((c = getchar()) > 47)
    r = 10 * r + c - 48;
  return r;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    N = read(), Q = read() + 1;

    // for (i = 1; i <= N; ++i) {
    //     std::cin >> a[i];
    //     b[i] = i * (a[i] - a[i - 1]) + b[i - 1];
    // }
    for (i = 1; i <= N; i++)
      b[i] = i * (a[i] = read()) + b[i - 1];

    for (i = N; i > 0; --i)
        r = i - (i & -i),
        a[i] -= a[r], b[i] -= b[r];

    while (--Q) {
        c = read(), y = (x = read()) + read();
        // std::cin >> c >> x >> y; y += x;

        if (c == 1) {
            s = 0;
            c = y - 1;
            while (c)
                s += y * a[c] - b[c],
                c -= c & -c;
            c = x - 1;
            while (c)
                s -= x * a[c] - b[c],
                c -= c & -c;

            std::cout << (s % 1000000007 + 1000000007) % 1000000007 << '\n';
        }
        else {
            v = read();
            // std::cin >> v;

            c = x;
            while (c <= N)
                a[c] += v,
                b[c] += x * v,
                c += c & -c;
            c = y;
            while (c <= N)
                a[c] -= v,
                b[c] -= y * v,
                c += c & -c;
        }
    }
    return 0;
}