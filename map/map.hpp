#ifndef SJTU_MAP_HPP
#define SJTU_MAP_HPP

#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
  class Key,
  class T,
  class Compare = std::less<Key>
> class map {
public:

  typedef pair<const Key, T> value_type;
  static const size_t pairSize = sizeof(value_type);

  class Node {
  public:
    value_type *value;
    bool color;
    Node *parent, *left, *right;

    explicit Node(const value_type &value, const bool color = false, Node *parent = nullptr)
    : value(static_cast<value_type*>(operator new(pairSize)))
    , color(color)
    , parent(parent)
    , left(nullptr)
    , right(nullptr)
    { new (this->value) value_type(value); }

    Node(const Node &other)
    : value(static_cast<value_type*>(operator new(pairSize)))
    , color(other.color)
    , parent(nullptr)
    , left(nullptr)
    , right(nullptr) {
      new (value) value_type(*other.value);
      if (other.left) left = new Node(*other.left), left->parent = this;
      if (other.right) right = new Node(*other.right), right->parent = this;
    }

    ~Node() {
      value->~value_type();
      operator delete(value);
      if (parent)
        if (this == parent->left) parent->left = nullptr;
        else parent->right = nullptr;
      delete left;
      delete right;
      }
    } *root;
    /*
     *      G              P
     *     / \            / \
     *    P   B    =>    X   G
     *   / \                / \
     *  X   A              A   B
     */
    void LL(Node *G) {
      G->left->parent = G->parent;
      if (G->parent)
        if (G->parent->left == G)
          G->parent->left = G->left;
        else
          G->parent->right = G->left;
      G->parent = G->left;
      G->left = G->parent->right;
      G->parent->right = G;
      if (G->left) G->left->parent = G;
      if (G == root) root = G->parent;
    }
    /*
     *      G                  P
     *     / \                / \
     *    B   P      =>      G   X
     *       / \            / \
     *      A   X          B   A
     */
    void RR(Node *G) {
      G->right->parent = G->parent;
      if (G->parent)
        if (G->parent->left == G)
          G->parent->left = G->right;
        else
          G->parent->right = G->right;
      G->parent = G->right;
      G->right = G->parent->left;
      G->parent->left = G;
      if (G->right) G->right->parent = G;
      if (G == root) root = G->parent;
    }
    /*
     *      G                 X
     *     / \               / \
     *    P   B             /   \
     *   / \       =>      P     G
     *  A   X             / \   / \
     *     / \           A   L R   B
     *    L   R
     */
    void LR(Node *G) { RR(G->left), LL(G); }
    /*
     *      G                   X
     *     / \                 / \
     *    B   P               /   \
     *       / \     =>      G     P
     *      X   A           / \   / \
     *     / \             B   L R   A
     *    L   R
     */
    void RL(Node *G) { LL(G->right), RR(G); }

  Compare less;
  size_t Size;

  class const_iterator;
  class iterator {
  public:
    Node *ptr;
    const map *cont;

    iterator() = default;

    iterator(const Node *ptr, const map *cont)
    : ptr(const_cast<Node*>(ptr))
    , cont(cont) {  }

    iterator(const iterator &other) = default;

    explicit iterator(const const_iterator &other)
    : ptr(const_cast<Node*>(other.ptr))
    , cont(other.cont) {  }

    iterator& operator=(const iterator &other) = default;

    iterator& operator=(const const_iterator &other) {
      ptr  = const_cast<Node*>(other.ptr);
      cont = other.cont;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      try { ++*this; } catch(...) { throw; }
      return tmp;
    }

    iterator & operator++() {
      if (ptr == nullptr) throw invalid_iterator();
      if (ptr->right) {
        ptr = ptr->right;
        while (ptr->left) ptr = ptr->left;
      }
      else {
        Node *P = ptr->parent;
        while (P && ptr == P->right)
          ptr = P, P = P->parent;
        ptr = P;
      }
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      try { --*this; } catch(...) { throw; }
      return tmp;
    }

    iterator & operator--() {
      if (ptr == nullptr) {
        if (!cont->root) throw invalid_iterator();
        ptr = cont->root;
        while (ptr->right) ptr = ptr->right;
      }
      else if (ptr->left) {
        ptr = ptr->left;
        while (ptr->right) ptr = ptr->right;
      }
      else {
        Node *P = ptr->parent;
        while (P && ptr == P->left)
          ptr = P, P = P->parent;
        if (!P) throw invalid_iterator();
        ptr = P;
      }
      return *this;
    }

    value_type & operator*() const { return *ptr->value; }

    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr && cont == rhs.cont; }

    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr && cont == rhs.cont; }

    bool operator!=(const iterator &rhs) const { return !operator==(rhs); }

    bool operator!=(const const_iterator &rhs) const { return !operator==(rhs); }

    value_type* operator->() const noexcept { return ptr->value; }
  };
  class const_iterator {
  public:
    const Node *ptr;
    const map *cont;

    const_iterator() = default;

    const_iterator(const Node *ptr, const map *cont)
    : ptr(ptr)
    , cont(cont) {  }

    const_iterator(const const_iterator &other) = default;

    explicit const_iterator(const iterator &other)
    : ptr(other.ptr)
    , cont(other.cont) {  }

    const_iterator& operator=(const iterator &other) {
      ptr = other.ptr;
      cont = other.cont;
      return *this;
    }
    const_iterator& operator=(const const_iterator &other) {
      if (this != &other) {
        ptr = other.ptr;
        cont = other.cont;
      }
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      try { ++*this; } catch(...) { throw; }
      return tmp;
    }

    const_iterator & operator++() {
      if (ptr == nullptr) throw invalid_iterator();
      if (ptr->right) {
        ptr = ptr->right;
        while (ptr->left) ptr = ptr->left;
      }
      else {
        Node *P = ptr->parent;
        while (P && ptr == P->right)
          ptr = P, P = P->parent;
        ptr = P;
      }
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp = *this;
      try { --*this; } catch(...) { throw; }
      return tmp;
    }

    const_iterator & operator--() {
      if (ptr == nullptr) {
        if (!cont->root) throw invalid_iterator();
        ptr = cont->root;
        while (ptr->right) ptr = ptr->right;
      }
      else if (ptr->left) {
        ptr = ptr->left;
        while (ptr->right) ptr = ptr->right;
      }
      else {
        Node *P = ptr->parent;
        while (P && ptr == P->left)
          ptr = P, P = P->parent;
        if (!P) throw invalid_iterator();
        ptr = P;
      }
      return *this;
    }

    const value_type & operator*() const { return *ptr->value; }

    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr && cont == rhs.cont; }

    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr && cont == rhs.cont; }

    bool operator!=(const iterator &rhs) const { return !operator==(rhs); }

    bool operator!=(const const_iterator &rhs) const { return !operator==(rhs); }

    const value_type* operator->() const noexcept { return ptr->value; }
  };

  map()
  : root(nullptr)
  , less(Compare())
  , Size(0) {  }

  map(const map &other)
  : root(nullptr)
  , less(other.less)
  , Size(other.Size)
  { if (other.root) root = new Node(*other.root); }

  map & operator=(const map &other) {
    if (this != &other) {
      delete root;
      if (other.root) root = new Node(*other.root);
      else root = nullptr;
      less = other.less;
      Size = other.Size;
    } return *this;
  }
  /**
   * TODO Destructors
   */
  ~map() { delete root; }
  /**
   * TODO
   * access specified element with bounds checking
   * Returns a reference to the mapped value of the element with key equivalent to key.
   * If no such element exists, an exception of type `index_out_of_bound'
   */
  T & at(const Key &key) {
    Node *cur = root;
    while (cur) {
      if (less(key, cur->value->first))
        cur = cur->left;
      else if (less(cur->value->first, key))
        cur = cur->right;
      else
        return cur->value->second;
    }
    throw index_out_of_bound();
  }

  const T & at(const Key &key) const {
    Node *cur = root;
    while (cur) {
      if (less(key, cur->value->first))
        cur = cur->left;
      else if (less(cur->value->first, key))
        cur = cur->right;
      else
        return cur->value->second;
    }
    throw index_out_of_bound();
  }

  T & operator[](const Key &key) { return insert(value_type(key, T())).first->second; }

  const T & operator[](const Key &key) const { try { return at(key); } catch(...) { throw; } }

  iterator begin() {
    if (!root) return end();
    Node *cur = root;
    while (cur->left) cur = cur->left;
    return iterator(cur, this);
  }
  const_iterator cbegin() const {
    if (!root) return cend();
    Node *cur = root;
    while (cur->left) cur = cur->left;
    return const_iterator(cur, this);
  }

  iterator end() { return iterator(nullptr, this); }

  const_iterator cend() const { return const_iterator(nullptr, this); }

  bool empty() const { return !root; }

  size_t size() const { return Size; }

  void clear() {
    delete root;
    root = nullptr;
    Size = 0;
  }

  pair<iterator, bool> insert(const value_type &value) {
    if (empty()) {
      Size = 1;
      return pair(iterator(root = new Node(value, 1), this), 1);
    }

    const Key &key = value.first;
    Node *G = root, *P = root, *X = root; // root1 at first
    while (X) { // P is G's child or root, X is P's child or root, if P0 then not U0

      // Adjust if L, R exist and L0, R0
      if (X->left && !X->left->color && X->right && !X->right->color) {
        X->color = X == root; // Keep root1
        X->left->color = X->right->color = 1;

        // Rotate and adjust if P0
        if (!P->color) { // if P0 then P is not root, so G1 and X0
          // L0, R0 at first, so LL1, LR1, RL1, RR1
          // LL1, ... may not exist

          if (G->left == P)
            if (P->left == X) {
              // Case 1: LL or RR
              LL(G), G->color = 0, P->color = 1;
              /*
               *      P1
               *     / \
               *    X0  G0
               *   / \
               *  L1  R1
               *  ||  ||
               *  LL1, ...
               */
              if (less(key, X->value->first))
                P = X, X = X->left;
              else if (less(X->value->first, key))
                P = X, X = X->right;
              else
                return pair(iterator(X, this), 0);
              /*
               *    P0 G0
               *    ||
               *   X1 L/R1
               *   ||
               *  LL1, ...
               */
            }
            else { // Case 2: LR or RL
              LR(G), G->color = 0, X->color = 1;
              /*
               *     X1
               *   /   \
               *  P0    G0
               *   \    /
               *    L1 R1
               *    || ||
               *   LL1, ...
               */
              if (less(key, X->value->first))
                X = P->right;
              else if (less(X->value->first, key))
                P = G, X = G->left;
              else
                return pair(iterator(X, this), 0);
              /*
               *    P0 G/oriP0
               *    ||
               *   X1 L/R1
               *   ||
               *  LL1, ...
               */
            }
          else
            if (P->right == X) {
              RR(G), G->color = 0, P->color = 1;
              if (less(key, X->value->first)) P = X, X = X->left;
              else if (less(X->value->first, key)) P = X, X = X->right;
              else return pair(iterator(X, this), 0);
            }
            else {
              RL(G), G->color = 0, X->color = 1;
              if (less(key, X->value->first)) P = G, X = G->right;
              else if (less(X->value->first, key)) X = P->left;
              else return pair(iterator(X, this), 0);
            }
          /*
           *    P0 U0
           *    ||
           *   X1 L/R1
           *   ||
           *  LL1, ...
           */
          // P0, U0 illegal
          if (less(key, X->value->first))
            G = P, P = X, X = X->left;
          else if (less(X->value->first, key))
            G = P, P = X, X = X->right;
          else
            return pair(iterator(X, this), 0);
          /*
           *    G0
           *    ||
           *   P1 U1
           *   ||
           *  X1 1
           */
          // Case ori L0, R0, P0: Adjust over!
          // but X may not exist or new L0, R0, so
          continue;
        }
        // Case ori L0, R0, P1: Adjust over!
      }
      // X exists and not L0, R0
      if (less(key, X->value->first)) // L exists
        G = P, P = X, X = X->left;
      else if (less(X->value->first, key))  // R exists
        G = P, P = X, X = X->right;
      else
        return pair(iterator(X, this), 0);
    }

    // X does not exist
    X = new Node(value, 0, P);
    if (less(key, P->value->first))
      P->left = X;
    else
      P->right = X;

    // root1, so if P0 then P is G's child and G1
    // ori X does not exist, so P is G's only child and P has no other child
    if (!P->color) {
      if (G->left == P) {
        if (P->left == X)
          LL(G), G->color = 0, P->color = 1;
        else
          LR(G), G->color = 0, X->color = 1;
      }
      else
        if (P->right == X)
          RR(G), G->color = 0, P->color = 1;
        else
          RL(G), G->color = 0, X->color = 1;
    }

    ++Size;
    return pair(iterator(X, this), 1);
  }
  /**
   * erase the element at pos.
   *
   * throw if pos pointed to a bad element (pos == this->end() || pos points an element out of this)
   */
  void erase(iterator pos) {
    if (pos.cont != this || pos == end()) throw invalid_iterator();
    if (!root->left && !root->right) {
      clear();
      return;
    }
    const Key &key = pos->first;
    Node *P = root, *X = root, *S = root;
    while (true) {
      if ((!X->left || X->left->color) && (!X->right || X->right->color)) {
        if ((!S->left || S->left->color) && (!S->right || S->right->color))
          P->color = 1, S->color = X->color = 0;
        else if (X == P->left)
          if (S->right && !S->right->color)
            RR(P), S->right->color = P->color = 1, S->color = X->color = 0;
          else
            RL(P), P ->color = 1, X->color = 0;
        else
          if (S->left && !S->left->color)
            LL(P), S->left->color = P->color = 1, S->color = X->color = 0;
          else
            LR(P), P->color = 1, X->color = 0;
      }
      else if (less(key, X->value->first)) {
        if (X->left->color) {
          RR(X), X->parent->color = 1, X->color = 0;
          P = X, X = P->left, S = P->right;
          continue;
        }
        P = X, X = P->left;
      }
      else if (less(X->value->first, key)) {
        if (X->right->color) {
          LL(X), X->parent->color = 1, X->color = 0;
          P = X, X = P->right, S = P->left;
          continue;
        }
        P = X, X = P->right;
      }
      else {
        if (X->right && !X->right->color) {
          Node *cur = X->right;
          if (!cur->left) {
            RR(X), root->color = cur->color = 1;
            if (X->left) LL(X);
            delete X;
            --Size;
            return;
          }
          while (cur->left) cur = cur->left;
          if (root == X) root = cur;
          std::swap(X, cur);
          std::swap(X->parent, cur->parent);
          std::swap(X->left, cur->left);
          std::swap(X->right, cur->right);
          std::swap(X->color, cur->color);
          if (X->parent)
            if (P->left == cur) P->left = X;
            else P->right = X;
          X->left->parent = X->right->parent = X;
          cur->parent->left = cur;
          if (cur->right) cur->right->parent = cur;
          P = X, X = X->right;
        }
        else {
          Node *cur = X->left;
          if (!cur->left) {
            LL(X), root->color = cur->color = 1;
            delete X;
            --Size;
            return;
          }
          while (cur->right) cur = cur->right;
          if (root == X) root = cur;
          std::swap(X, cur);
          std::swap(X->parent, cur->parent);
          std::swap(X->left, cur->left);
          std::swap(X->right, cur->right);
          std::swap(X->color, cur->color);
          if (X->parent)
            if (P->left == cur) P->left = X;
            else P->right = X;
          X->left->parent = X->right->parent = X;
          cur->parent->right = cur;
          if (cur->left) cur->left->parent = cur;
          P = X, X = X->left;
        }
      }
      if (!X->left) {
        delete X;
        --Size;
        root->color = 1;
        return;
      }
      if (less(key, X->value->first))
        P = X, X = P->left, S = P->right;
      else if (less(X->value->first, key))
        P = X, X = P->right, S = P->left;
      else {
        Node *cur = X->right;
        while (cur->left) cur = cur->left;
        if (root == X) root = cur;
        std::swap(X, cur);
        std::swap(X->parent, cur->parent);
        std::swap(X->left, cur->left);
        std::swap(X->right, cur->right);
        std::swap(X->color, cur->color);
        if (X->right == X) std::swap(X->right, cur->parent);
        if (X->parent)
          if (P->left == cur)
            P->left = X;
          else
            P->right = X;
        X->left->parent = X->right->parent = X;
        if (X->right != cur) cur->parent->left = cur;
        if (cur->right) cur->right->parent = cur;
        P = X, X = P->right, S = P->left;
      }
    }
  }

  size_t count(const Key &key) const {
    Node *cur = root;
    while (cur) {
      if (less(key, cur->value->first))
        cur = cur->left;
      else if (less(cur->value->first, key))
        cur = cur->right;
      else
        return 1;
    }
    return 0;
  }

  iterator find(const Key &key) {
    Node *cur = root;
    while (cur) {
      if (less(key, cur->value->first))
        cur = cur->left;
      else if (less(cur->value->first, key))
        cur = cur->right;
      else
        return iterator(cur, this);
    }
    return end();
  }

  const_iterator find(const Key &key) const {
    Node *cur = root;
    while (cur) {
      if (less(key, cur->value->first))
        cur = cur->left;
      else if (less(cur->value->first, key))
        cur = cur->right;
      else
        return const_iterator(cur, this);
    }
    return cend();
  }
};

}

#endif