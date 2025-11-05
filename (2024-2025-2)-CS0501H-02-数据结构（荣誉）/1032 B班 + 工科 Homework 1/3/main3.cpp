#include <iostream>
#include <string>

constexpr int S = 4096;

struct node {
  std::string str;
  node* next;
  node* prev;
  node() : next(nullptr), prev(nullptr) {
    str = "";
  }
} *head, *ptr, *tail;
unsigned long pos = 0;

void Anchor();
void Summon();
void Annihilate();
void Manifest();
void Rewind();
void Surge();

void initialize() {
  head = new node();
  ptr  = new node();
  tail = new node();
  head->next = ptr;
  tail->prev = ptr;
  ptr->next  = tail;
  ptr->prev  = head;
}

unsigned long split_pos;
node *split_tmp1, *split_tmp2;
void split() {
  if (ptr->str.size() < S << 1) return;
  split_tmp1 = ptr;
  split_tmp2 = ptr->next;
  for (split_pos = S; split_pos < ptr->str.size(); split_pos += S) {
    split_tmp1->next       = new node();
    split_tmp1->next->prev = split_tmp1;
    split_tmp1             = split_tmp1->next;
    split_tmp1->str        = ptr->str.substr(split_pos, S);
  }
  split_tmp1->next = split_tmp2;
  split_tmp2->prev = split_tmp1;
  ptr->str = ptr->str.substr(0, S);
}

unsigned long merge_size;
node *merge_tmp;
void merge() {
  if (ptr == tail || ptr->next == tail) return;
  merge_tmp  = ptr->next;
  merge_size = ptr->str.size() + merge_tmp->str.size();
  while (merge_size < S && merge_tmp != tail) {
    ptr->str   += merge_tmp->str;
    merge_tmp   = merge_tmp->next;
    merge_size += merge_tmp->str.size();
    delete merge_tmp->prev;
  }
  ptr->next       = merge_tmp;
  merge_tmp->prev = ptr;
}

void check() {
  if (ptr == tail) {
    tail       = new node();
    ptr->next  = tail;
    tail->prev = ptr;
    return;
  }
  merge();
  while (pos >= ptr->str.size() && ptr != tail) {
    pos -= ptr->str.size();
    ptr  = ptr->next;
    merge();
  }
  if (ptr == tail) {
    tail       = new node();
    ptr->next  = tail;
    tail->prev = ptr;
  }
}

char read_ch;
void read(unsigned long read_n, std::string &read_s) {
  ++read_n;
  read_s.clear();
  while (--read_n) {
    do std::cin.get(read_ch);
    while (read_ch == '\n');
    read_s += read_ch;
  }
}

void cleanup() {
  ptr = head->next;
  while (ptr != nullptr) {
    delete ptr->prev;
    ptr = ptr->next;
  }
  delete tail;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  initialize();
  int t;
  std::string command;
  std::cin >> t;
  ++t;
  while (--t) {
    std::cin >> command;
    if      (command == "Anchor")     Anchor();
    else if (command == "Summon")     Summon();
    else if (command == "Annihilate") Annihilate();
    else if (command == "Manifest")   Manifest();
    else if (command == "Rewind")     Rewind();
    else if (command == "Surge")      Surge();
  }
  cleanup();
  return 0;
}

void Anchor() {
  std::cin >> pos;
  ptr = head->next;
  check();
}

unsigned long summon_n;
std::string summon_s;
void Summon() {
  std::cin >> summon_n;
  read(summon_n, summon_s);
  check();
  ptr->str.insert(pos, summon_s);
  split();
  check();
}

unsigned long annihilate_n;
node *annihilate_tmp, *annihilate_tmp2;
void Annihilate() {
  std::cin >> annihilate_n;
  check();
  if (annihilate_n + pos < ptr->str.size()) {
    ptr->str.erase(pos, annihilate_n);
    check();
    return;
  }
  annihilate_n -= ptr->str.size() - pos;
  ptr->str = ptr->str.substr(0, pos);
  if (pos != 0) ptr = ptr->next;
  pos = 0;
  annihilate_tmp = ptr->prev;
  while (annihilate_n >= ptr->str.size() && ptr != tail) {
    annihilate_n -= ptr->str.size();
    ptr = ptr->next;
    delete ptr->prev;
  }
  if (ptr != tail) ptr->str = ptr->str.substr(annihilate_n);
  ptr->prev = annihilate_tmp;
  annihilate_tmp->next = ptr;
  check();
}

unsigned long manifest_n;
node *manifest_tmp;
void Manifest() {
  std::cin >> manifest_n;
  check();
  if (manifest_n + pos <= ptr->str.size()) {
    std::cout << ptr->str.substr(pos, manifest_n) << '\n';
    return;
  }
  std::cout << ptr->str.substr(pos);
  manifest_n  -= ptr->str.size() - pos;
  manifest_tmp = ptr->next;
  while (manifest_n > 0 && manifest_n >= manifest_tmp->str.size()) {
    std::cout << manifest_tmp->str;
    manifest_n  -= manifest_tmp->str.size();
    manifest_tmp = manifest_tmp->next;
  }
  std::cout << manifest_tmp->str.substr(0, manifest_n);
  std::cout << '\n';
}

void Rewind() {
  if (pos > 0) {
    --pos;
    return;
  }
  do ptr = ptr->prev;
  while (ptr->str.size() == 0);
  pos = ptr->str.size() - 1;
  merge();
}

void Surge() {
  ++pos;
  check();
}