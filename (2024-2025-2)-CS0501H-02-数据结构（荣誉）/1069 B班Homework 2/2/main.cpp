#include <iostream>

inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
  return x * f;
}

struct node {
  int i;
  long long s;
  node *prev, *next;

  node(const int i, const long long s, node *prev, node *next)
  : i(i), s(s), prev(prev), next(next) {  }
} *head, *tail, *tmp;

int n, m, i, p[10000000], r[10000000];
long long s[10000001], si, a;

int main() {
  n = read(), m = read();
  for (i = 0; i < n; ++i)
    s[i + 1] = s[i] + (p[i] = read());

  head = new node(0, 0, nullptr, nullptr);
  tail = new node(0, 0, nullptr, nullptr);

  head->next = tail->prev
  = new node(n, s[n], head, tail);
  r[n - 1] = n;

  for (i = n - 2; i >= 0; --i) {
    if (head->next->i > i + m) {
      tmp = head->next;
      head->next = tmp->next;
      head->next->prev = head;
      delete tmp;
    }

    si = s[i + 1];
    tmp = tail->prev;
    while (tmp != head &&
      tmp->s <= si) {
      tmp = tmp->prev;
      delete tmp->next;
    }

    tail->prev = tmp->next
    = new node(i + 1, si, tmp, tail);
    r[i] = head->next->i;
  }

  a = s[r[0]];
  for (i = 1; i < n; ++i)
    a = std::max(a, s[r[i]] - s[i]);
  std::cout << a;
  return 0;
}