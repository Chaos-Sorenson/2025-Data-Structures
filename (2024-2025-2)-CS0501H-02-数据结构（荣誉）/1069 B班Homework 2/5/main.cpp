#include <iostream>

struct node {
  int id, h;
  long long s1, s;
  node *next;
  node (const int id, const int h, node *next, const long long s1, const long long s)
  : id(id), h(h), s1(s1), s(s), next(next) {  }
} *head, *tmp;
char a[2000][2001];
int h[2000][2000];

int main() {
  int N, M, H, i, j;
  std::cin >> N >> M;
  for (i = 0; i < N; ++i)
    for (j = 0; j < M; ++j)
      std::cin >> a[i][j];
  for (j = 0; j < M; ++j)
    for (i = 0, H = 1; i < N; ++i, ++H) {
      if (a[i][j] == '#') H = 0;
      h[i][j] = H;
    }

  int sH, dID, sdID;
  long long res = 0;
  for (i = 0; i < N; ++i) {
    head = new node(-1, 0, nullptr, 0, 0);
    for (j = 0; j < M; ++j) {
      H = h[i][j];
      sH = H * (H + 1) >> 1;
      while (head->h > H) {
        tmp = head;
        head = head->next;
        delete tmp;
      }
      dID = j - head->id;
      sdID = dID * (dID + 1) >> 1;
      head = new node(j, H, head, head->s1 + sH * dID, head->s + sH * sdID + head->s1 * dID);
      res += head->s;
    }
    while (head) {
      tmp = head;
      head = head->next;
      delete tmp;
    }
  }
  std::cout << res;
  return 0;
}