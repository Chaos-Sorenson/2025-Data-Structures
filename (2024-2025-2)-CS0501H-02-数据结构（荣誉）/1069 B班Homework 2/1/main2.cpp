#include <iostream>

struct node {
  long long l, r;
  unsigned int layer;
  node *next;
  node(const long long l, const long long r, const int layer, node *next)
  : l(l), r(r), layer(layer), next(next) {  }
};

int main() {
  long long A, B, ret = 1;
  std::cin >> A >> B;
  node *head = new node(A, B, 0, nullptr), *tmp;
  while (head != nullptr) {
    if (head->layer == 0) {
      if (head->l == 0) {
        ret = head->r;
        tmp = head;
        head = head->next;
        delete tmp;
      }
      else {
        head->layer = 1;
        head = new node(head->r % head->l, head->l, 0, head);
      }
    }
    else if (head->layer == 1) {
      tmp = head;
      head = head->next;
      delete tmp;
    }
  }
  std::cout << ret;
  return 0;
}