#include <iostream>
#include <string>

constexpr int S = 1024;

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

// initialize: build list
void initialize() {
  head = new node();
  ptr  = new node();
  tail = new node();
  head->next = ptr;
  tail->prev = ptr;
  ptr->next  = tail;
  ptr->prev  = head;
}

// split: split node so that S <= new size <= S * 3/2
// let old size = Q * S + R, Q >= 2, 0 <= R < S,
// then new size = S + R / Q < S + S/2
unsigned long split_old_size, split_new_size, Q, R, split_pos;
node *split_node, *split_tmp, *split_tmp2;
void split() {
  split_node = ptr;
  split_old_size = ptr->str.size();
  Q = split_old_size / S;
  R = split_old_size % S;
  if (Q < 2) return;
  split_new_size = S + R / Q;
  split_tmp2     = ptr->next;
  for (split_pos = split_new_size; split_pos < split_old_size; split_pos += split_new_size) {
    split_node->next = split_tmp = new node();
    split_tmp->prev  = split_node;
    split_node       = split_tmp;
    split_node->str  = ptr->str.substr(split_pos, split_new_size);
  }
  split_node->next = split_tmp2;
  split_tmp2->prev = split_node;
  ptr->str.erase(split_new_size);
}

// merge: merge with next node until S <= size < 2S
unsigned long merge_size;
node *merge_tmp;
void merge() {
  merge_size = ptr->str.size();
  merge_tmp  = ptr->next;
  if (ptr == tail || merge_tmp == tail) return;
  while (merge_size < S && merge_tmp != tail) {
    merge_size += merge_tmp->str.size();
    ptr->str   += merge_tmp->str;
    merge_tmp   = merge_tmp->next;
    delete merge_tmp->prev;
  }
  ptr->next = merge_tmp;
  merge_tmp->prev  = ptr;
  split();
}

// check: move ptr until pos is legal
void check() {
  merge();
  while (pos >= ptr->str.size() && ptr != tail) {
    pos -= ptr->str.size();
    ptr  = ptr->next;
    merge();
  }
  if (ptr == tail) {
    tail = ptr->next = new node();
    tail->prev = ptr;
  }
}

// read: read n char to s and ignore '\n'
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

// Anchor: place the "pointer" in front of char with the index of n, 0_based
// that is, after the n-th char, 1_based
void Anchor() {
  std::cin >> pos;
  ptr = head->next;
  check();
}

// Summon: str.insert(pos, s) and split
unsigned long summon_n;
std::string summon_s;
void Summon() {
  std::cin >> summon_n;
  read(summon_n, summon_s);
  ptr->str.insert(pos, summon_s);
  split();
  check();
}

// Annihilate: str.erase(pos, pos + n) and merge
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
  while (manifest_n > 0) {
    std::cout << manifest_tmp->str.substr(0, manifest_n);
    manifest_n  -= manifest_tmp->str.size();
    manifest_tmp = manifest_tmp->next;
  }
  std::cout << '\n';
}

// Rewind: --pos
void Rewind() {
  --pos;
  while (pos < 0) {
    ptr = ptr->prev;
    pos = ptr->str.size() - 1;
  }
}

//Surge: ++pos
void Surge() {
  ++pos;
  check();
}