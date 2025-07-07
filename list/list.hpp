#ifndef SJTU_LIST_HPP
#define SJTU_LIST_HPP

#include "exceptions.hpp"
#include "algorithm.hpp"

#include <climits>
#include <cstddef>

namespace sjtu {
template<typename T>
class list {
protected:
  class node {
  public:
    T *data;
    node *next, *prev;

    node() : data(nullptr), next(nullptr), prev(nullptr) {  }

    explicit node(const T &e) : data(static_cast<T*>(operator new(sizeofT))),
      next(nullptr), prev(nullptr) { new (data) T(e); }

    node (const node *other, const node *prev) : data(static_cast<T*>(operator new(sizeofT))),
      next(nullptr), prev(const_cast<node*>(prev)) { new (data) T(*other->data); }

    ~node() { if (data) { data->~T(); ::operator delete(data); } }
  };

  node *head, *tail;
  size_t _size;
  static const int sizeofT = sizeof(T);

  node *insert(node *pos, node *cur) {
    if (pos == head) throw runtime_error();
    pos->prev->next = cur;
    cur->prev = pos->prev;
    cur->next = pos;
    pos->prev = cur;
    ++_size;
    return cur;
  }

  node *erase(node *pos) {
    if (pos == head || pos == tail) throw runtime_error();
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    --_size;
    return pos;
  }

public:
  class const_iterator;

  class iterator {
  public:
    node *ptr;
    const list *container;

    explicit iterator(const node *ptr, const list *container) : ptr(const_cast<node*>(ptr)), container(container) {  }

    iterator(const iterator &it) : ptr(it.ptr), container(it.container)  {  }

    explicit iterator(const const_iterator &it) : ptr(const_cast<node*>(it.ptr)), container(it.container)  {  }

    iterator operator++(int) {
      if (ptr->next == nullptr) throw invalid_iterator();
      ptr = ptr->next;
      return iterator(ptr->prev, container);
    }

    iterator & operator++() {
      if (ptr->next == nullptr) throw invalid_iterator();
      ptr = ptr->next;
      return *this;
    }

    iterator operator--(int) {
      if (ptr->prev == container->head || ptr->prev == nullptr) throw invalid_iterator();
      ptr = ptr->prev;
      return iterator(ptr->next, container);
    }

    iterator & operator--() {
      if (ptr->prev == container->head || ptr->prev == nullptr) throw invalid_iterator();
      ptr = ptr->prev;
      return *this;
    }

    T & operator *() const {
      if (ptr == container->head || ptr == container->tail) throw invalid_iterator();
      return *ptr->data;
    }

    T * operator ->() const noexcept {
      if (ptr == container->head || ptr == container->tail) throw invalid_iterator();
      return ptr->data;
    }

    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }

    bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }
    };

  class const_iterator {
  public:
    const node *ptr;
    const list *container;

    explicit const_iterator(const node *ptr, const list *container) : ptr(ptr), container(container) {  }

    const_iterator(const const_iterator &it) : ptr(it.ptr), container(it.container) {  }

    explicit const_iterator(const iterator &it) : ptr(it.ptr), container(it.container) {  }

    const_iterator operator++(int) {
      if (ptr->next == nullptr) throw invalid_iterator();
      ptr = ptr->next;
      return const_iterator(ptr->prev, container);
    }

    const_iterator & operator++() {
      if (ptr->next == nullptr) throw invalid_iterator();
      ptr = ptr->next;
      return *this;
    }

    const_iterator operator--(int) {
      if (ptr->prev == container->head || ptr->prev == nullptr) throw invalid_iterator();
      ptr = ptr->prev;
      return const_iterator(ptr->next, container);
    }

    const_iterator operator--() {
      if (ptr->prev == container->head || ptr->prev == nullptr) throw invalid_iterator();
      ptr = ptr->prev;
      return *this;
    }

    const T & operator *() const {
      if (ptr == container->head || ptr == container->tail) throw invalid_iterator();
      return *ptr->data;
    }

    const T * operator ->() const noexcept {
      if (ptr == container->head || ptr == container->tail) throw invalid_iterator();
      return ptr->data;
    }

    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }

    bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }
    };

    list() : head(new node()), tail(new node()), _size(0) {
      head->next = tail;
      tail->prev = head;
    }

    list(const list &other) : head(new node()), tail(new node()), _size(other._size) {
      node *cur = other.head->next, *tmp = head;
      while (cur != other.tail) {
        tmp = tmp->next = new node(cur, tmp);
        cur = cur->next;
      }
      tmp->next  = tail;
      tail->prev = tmp;
    }

    virtual ~list() {
      do {
        head = head->next;
        delete head->prev;
      } while (head != tail);
      delete tail;
    }

    list &operator=(const list &other) {
      if (this != &other) {
        node *tmp = head->next, *cur = other.head->next;
        while (tmp != tail) {
          tmp = tmp->next;
          delete tmp->prev;
        }
        tmp = head;
        while (cur != other.tail) {
          tmp = tmp->next = new node(cur, tmp);
          cur = cur->next;
        }
        tmp->next  = tail;
        tail->prev = tmp;
      }
      _size = other._size;
      return *this;
    }

    const T & front() const {
      if (_size == 0) throw container_is_empty();
      return *head->next->data;
    }

    const T & back() const {
      if (_size == 0) throw container_is_empty();
      return *tail->prev->data;
    }

    iterator begin() { return iterator(head->next, this); }

    const_iterator cbegin() const { return const_iterator(head->next, this); }

    iterator end() { return iterator(tail, this); }

    const_iterator cend() const { return const_iterator(tail, this); }

    virtual bool empty() const { return _size == 0; }

    virtual size_t size() const { return _size; }

    virtual void clear() {
      node *tmp = head->next;
      while (tmp != tail) {
        tmp = tmp->next;
        delete tmp->prev;
      }
      head->next = tail;
      tail->prev = head;
      _size = 0;
    }

    virtual iterator insert(iterator pos, const T &value) {
      if (pos.container != this || pos.ptr == head) throw invalid_iterator();
      return iterator(insert(pos.ptr, new node(value)), this);
    }

    virtual iterator erase(iterator pos) {
      if (pos.container != this || pos.ptr == head) throw invalid_iterator();
      if (_size == 0) throw container_is_empty();
      if (pos.ptr == tail || pos.ptr == head) throw invalid_iterator();
      node *tmp = pos.ptr->next;
      tmp->prev = pos.ptr->prev;
      tmp->prev->next = tmp;
      --_size;
      delete pos.ptr;
      return iterator(tmp, this);
    }

    void push_back(const T &value) { insert(tail, new node(value)); }

    void pop_back() {
      if (_size == 0) throw container_is_empty();
      node *tmp = tail->prev;
      tail->prev = tmp->prev;
      tail->prev->next = tail;
      --_size;
      delete tmp;
    }

    void push_front(const T &value) { insert(head->next, new node(value)); }

    void pop_front() {
      if (_size == 0) throw container_is_empty();
      node *tmp = head->next;
      head->next = tmp->next;
      head->next->prev = head;
      --_size;
      delete tmp;
    }

    void qsort(node **begin, node **end) {
      const int len = end - begin;
      if (len <= 1) return ;
      node **i = begin, **j = end - 1;
      node *pivot = *(begin + (len + 1) / 2 - 1);
      while (j - i >= 0){
        while (*(*i)->data < *pivot->data) ++i;
        while (*pivot->data < *(*j)->data) --j;
        if (j - i >= 0){
          std::swap(*i, *j);
          ++i, --j;
        }
      }
      if (j - begin > 0) qsort(begin, i);
      if (end - i > 1) qsort(i, end);
    }

    void sort() {
      if (_size < 2) return;
      const size_t s = _size;
      node *arr[s];
      arr[0] = head->next;
      for (int i = 1; i < s; ++i) arr[i] = arr[i - 1]->next;
      qsort(arr, arr + s);
      head->next = arr[0];
      arr[0]->prev = head;
      for (int i = 1; i < s; ++i) {
        arr[i - 1]->next = arr[i];
        arr[i]->prev = arr[i - 1];
      }
      arr[s - 1]->next = tail;
      tail->prev = arr[s - 1];
    }

    void merge(list &other) {
      if (other._size == 0) return;
      if (_size == 0) {
        head->next = other.head->next;
        tail->prev = other.tail->prev;
        head->next->prev = head;
        tail->prev->next = tail;
        other.head->next = other.tail;
        other.tail->prev = other.head;
        _size = other._size;
        other._size = 0;
        return;
      }
      node *tmp = head->next, *cur = other.head->next;
      while (tmp != tail && cur != other.tail) {
        if (*cur->data < *tmp->data) {
          cur = cur->next;
          tmp->prev->next = cur->prev;
          cur->prev->prev = tmp->prev;
          cur->prev->next = tmp;
          tmp->prev = cur->prev;
        } else tmp = tmp->next;
      }
      if (cur != other.tail) {
        tail->prev->next = cur;
        cur->prev = tail->prev;
        tail->prev = other.tail->prev;
        tail->prev->next = tail;
      }
      other.head->next = other.tail;
      other.tail->prev = other.head;
      _size += other._size;
      other._size = 0;
    }

    void reverse() {
      node *tmp = head;
      while (tmp != nullptr) {
        std::swap(tmp->prev, tmp->next);
        tmp = tmp->prev;
      }
      std::swap(head, tail);
    }

    void unique() {
      if (_size < 2) return;
      node *tmp = head->next, *tmp2 = nullptr;
      while (tmp->next != tail) {
        if (*tmp->data == *tmp->next->data) {
          tmp2 = tmp->next;
          tmp->next = tmp2->next;
          tmp->next->prev = tmp;
          delete tmp2;
          --_size;
        } else tmp = tmp->next;
      }
    }
};

}

#endif //SJTU_LIST_HPP