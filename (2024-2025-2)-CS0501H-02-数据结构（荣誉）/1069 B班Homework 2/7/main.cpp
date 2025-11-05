#include <iostream>

int a, b, m, n, i, j, h[1000][1000],
rm[1000][1000], rM[1000][1000],
cm[1000][1000], cM[1000][1000],
res = 2147483647;

struct node {
  int id, val;
  node *prev, *next;

  explicit node(const int id = 0, const int val = 0, node *prev = nullptr, node *next = nullptr)
  : id(id), val(val), prev(prev), next(next) {  }
} *head, *tail, *tmp;

int main() {
  std::cin >> a >> b >> m >> n;
  for (i = 0; i < a; ++i)
    for (j = 0; j < b; ++j)
      std::cin >> h[i][j];

  head = new node();
  tail = new node();
  head->next = tail;
  tail->prev = head;

  if (n > 1) {
    for (i = 0; i < a; ++i) {
      head->next = tail->prev
      = new node(0, h[i][0], head, tail);
      for (j = 1; j < b; ++j) {
        if (head->next->id <= j - n) {
          tmp = head->next;
          head->next = tmp->next;
          tmp->next->prev = head;
          delete tmp;
        }
        while (tail->prev != head &&
          tail->prev->val >= h[i][j]) {
          tmp = tail->prev;
          tail->prev = tmp->prev;
          delete tmp;
        } tail->prev->next = tail;
        tail->prev = tail->prev->next
        = new node(j, h[i][j], tail->prev, tail);
        rm[i][j] = head->next->val;
      }
      while (tail->prev != head) {
        tmp = tail->prev;
        tail->prev = tmp->prev;
        delete tmp;
      } head->next = tail;
    }
    for (i = 0; i < a; ++i) {
      head->next = tail->prev =
      new node(0, h[i][0], head, tail);
      for (j = 1; j < b; ++j) {
        if (head->next->id <= j - n) {
          tmp = head->next;
          head->next = tmp->next;
          tmp->next->prev = head;
          delete tmp;
        }
        while (tail->prev != head &&
          tail->prev->val <= h[i][j]) {
          tmp = tail->prev;
          tail->prev = tmp->prev;
          delete tmp;
        } tail->prev->next = tail;
        tail->prev = tail->prev->next
        = new node(j, h[i][j], tail->prev, tail);
        rM[i][j] = head->next->val;
      }
      while (tail->prev != head) {
        tmp = tail->prev;
        tail->prev = tmp->prev;
        delete tmp;
      } head->next = tail;
    }
  }
  else
    for (i = 0; i < a; ++i)
      for (j = 0; j < b; ++j)
        rM[i][j] = rm[i][j] = h[i][j];

  if (m > 1) {
    for (j = n - 1; j < b; ++j) {
      head->next = tail->prev
      = new node(0, rm[0][j], head, tail);
      for (i = 1; i < a; ++i) {
        if (head->next->id <= i - m) {
          tmp = head->next;
          head->next = tmp->next;
          tmp->next->prev = head;
          delete tmp;
        }
        while (tail->prev != head &&
          tail->prev->val >= rm[i][j]) {
          tmp = tail->prev;
          tail->prev = tmp->prev;
          delete tmp;
        } tail->prev->next = tail;
        tail->prev = tail->prev->next
        = new node(i, rm[i][j], tail->prev, tail);
        cm[i][j] = head->next->val;
      }
      while (tail->prev != head) {
        tmp = tail->prev;
        tail->prev = tmp->prev;
        delete tmp;
      } head->next = tail;
    }
    for (j = n - 1; j < b; ++j) {
      head->next = tail->prev
      = new node(0, rM[0][j], head, tail);
      for (i = 1; i < a; ++i) {
        if (head->next->id <= i - m) {
          tmp = head->next;
          head->next = tmp->next;
          tmp->next->prev = head;
          delete tmp;
        }
        while (tail->prev != head &&
          tail->prev->val <= rM[i][j]) {
          tmp = tail->prev;
          tail->prev = tmp->prev;
          delete tmp;
        } tail->prev->next = tail;
        tail->prev = tail->prev->next
        = new node(i, rM[i][j], tail->prev, tail);
        cM[i][j] = head->next->val;
      }
      while (tail->prev != head) {
        tmp = tail->prev;
        tail->prev = tmp->prev;
        delete tmp;
      } head->next = tail;
    }
  }
  else
    for (i = m - 1; i < a; ++i)
      for (j = 0; j < b; ++j)
        cm[i][j] = rm[i][j],
        cM[i][j] = rM[i][j];

  for (i = m - 1; i < a; ++i)
    for (j = n - 1; j < b; ++j)
        res = std::min(res, cM[i][j] - cm[i][j]);
  std::cout << res;
  return 0;
}