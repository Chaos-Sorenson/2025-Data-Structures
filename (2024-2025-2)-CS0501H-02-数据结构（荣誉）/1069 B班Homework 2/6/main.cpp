#include <iostream>

struct node {
  int i, d, w;
  node *next;
  explicit node(const int i = 0, const int d = 0, const int w = 0, node *next = nullptr)
  : i(i), d(d), w(w), next(next) {}
} *a[300001], *head, *tmp;
int res[300001], n, i, d, w;

void down(int i, const int n) {
  i <<= 1;
  while (i <= n) {
    if (i < n && a[i]->d < a[i + 1]->d) ++i;
    if (a[i]->d <= a[i >> 1]->d) return;
    std::swap(a[i], a[i >> 1]);
    i <<= 1;
  }
}

int main() {
  std::cin >> n;
  for (i = 1; i <= n; ++i) {
    std::cin >> d >> w;
    a[i] = new node(i, d, w);
  }

  for (i = n >> 1; i > 0; --i)
    down(i, n);
  for (i = n; i > 1; --i)
    std::swap(a[1], a[i]),
    down(1, i - 1);

  head = a[1];
  for (i = 2; i <= n; ++i) {
    d = a[i]->d, w = a[i]->w;
    while (head && w >= head->w) {
      res[head->i] = d;
      head = head->next;
    }
    a[i]->next = head;
    head = a[i];
  }

  while (head) {
    res[head->i] = -1;
    head = head->next;
  }

  for (int i = 1; i <= n; ++i) {
    std::cout << res[a[i]->i] << ' ';
    delete a[i];
  }

  return 0;
}