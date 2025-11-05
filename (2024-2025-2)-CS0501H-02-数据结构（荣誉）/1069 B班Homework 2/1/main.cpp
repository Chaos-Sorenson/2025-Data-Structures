#include <iostream>

int main() {
  long long int A, B, tmp;
  std::cin >> A >> B;
  while (A != 0) {
    tmp = A;
    A = B % A;
    B = tmp;
  }
  std::cout << B;
  return 0;
}