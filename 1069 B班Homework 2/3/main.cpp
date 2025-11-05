#include <iostream>

struct node {
  int val, id;
  node* next;
  node(const int val, const int id, node* next)
  : val(val), id(id), next(next) {}
};

int l[100000], r[100000];
long long a[100001], sum[100001];

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> a[i];
    sum[i + 1] = sum[i] + a[i];
  }
  node *head = new node(a[0], 0, nullptr), *tmp;
  for (int i = 1; i < n; ++i) {
    while (head && head->val > a[i]) {
      r[head->id] = i;
      tmp = head;
      head = head->next;
      delete tmp;
    }
    head = new node(a[i], i, head);
  }
  while (head) {
    r[head->id] = n;
    tmp = head;
    head = head->next;
    delete tmp;
  }
  head = new node(a[n - 1], n - 1, nullptr);
  for (int i = n - 2; i >= 0; --i) {
    while (head && head->val > a[i]) {
      l[head->id] = i + 1;
      tmp = head;
      head = head->next;
      delete tmp;
    }
    head = new node(a[i], i, head);
  }
  while (head) {
    tmp = head;
    head = head->next;
    delete tmp;
  }
  long long res = a[0] * (sum[r[0]] - sum[l[0]]);
  for (int i = 1; i < n; ++i) res = std::max(res, a[i] * (sum[r[i]] - sum[l[i]]));
  std::cout << res;
  return 0;
}