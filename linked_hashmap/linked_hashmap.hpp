#ifndef SJTU_LINKEDHASHMAP_HPP
#define SJTU_LINKEDHASHMAP_HPP

#include <functional>
#include <cstddef>
#include "utility.hpp"
#include "exceptions.hpp"

namespace sjtu {

template<
  class Key,
  class T,
  class Hash = std::hash<Key>,
  class Equal = std::equal_to<Key>
> class linked_hashmap {
public:
  typedef pair<const Key, T> value_type;
  struct Node {
  	value_type value;
  	Node *prev = nullptr,
         *next = nullptr,
  	     *hash_prev = nullptr,
         *hash_next = nullptr;
    explicit Node(const value_type & value) : value(value) {  }
  } *head, *tail, **buckets;
  size_t _size, bucket_count;
  Hash hasher = Hash();
  Equal equal = Equal();

  void rehash(const size_t new_count) {
    bucket_count = new_count;
  	delete [] buckets;
    buckets = new Node*[bucket_count]();
  	Node *cur = head->next;
  	while (cur != tail) {
      size_t index = hasher(cur->value.first) % bucket_count;
      cur->hash_next = buckets[index];
      if (cur->hash_next != nullptr)
        cur->hash_next->hash_prev = cur;
      buckets[index] = cur;
  	  cur->hash_prev = nullptr;
      cur = cur->next;
  	}
  }

  class const_iterator;
  class iterator {
  public:
    Node *ptr = nullptr;
    linked_hashmap *cont = nullptr;

    iterator() = default;
  	iterator(const Node *ptr, const linked_hashmap *cont) :
        ptr(const_cast<Node*>(ptr)),
        cont(const_cast<linked_hashmap*>(cont)) {  }
    iterator(const iterator &other) :
        ptr(other.ptr),
        cont(other.cont) {  }

    iterator operator++(int) {
      iterator tmp(*this);
      ++*this;
      return tmp;
  	}
    iterator & operator++() {
      if (ptr == cont->tail)
        throw index_out_of_bound();
      ptr = ptr->next;
      return *this;
  	}

    iterator operator--(int) {
      iterator tmp(*this);
      --*this;
      return tmp;
  	}
    iterator & operator--() {
      if (ptr == cont->head->next)
        throw index_out_of_bound();
      ptr = ptr->prev;
      return *this;
  	}

    value_type & operator*() const {
      return ptr->value;
  	}

    bool operator==(const iterator &rhs) const {
      return ptr == rhs.ptr;
  	}
    bool operator==(const const_iterator &rhs) const {
      return ptr == rhs.ptr;
  	}

    bool operator!=(const iterator &rhs) const {
      return ptr != rhs.ptr;
  	}
    bool operator!=(const const_iterator &rhs) const {
      return ptr != rhs.ptr;
  	}

    value_type* operator->() const noexcept {
      return &ptr->value;
  	}
  };

  class const_iterator {
  public:
    const Node *ptr = nullptr;
    const linked_hashmap *cont = nullptr;
    const_iterator() = default;
    const_iterator(const Node *ptr, const linked_hashmap *cont) :
        ptr(ptr),
        cont(cont) {  }
    const_iterator(const const_iterator &other) :
        ptr(other.ptr),
        cont(other.cont) {  }
    explicit const_iterator(const iterator &other) :
        ptr(other.ptr),
        cont(other.cont) {  }
    const_iterator & operator=(const iterator &other) {
      ptr = other.ptr;
      cont = other.cont;
      return *this;
    }

  	const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++*this;
      return tmp;
    }
    const_iterator & operator++() {
	  if (ptr == cont->tail)
	    throw index_out_of_bound();
      ptr = ptr->next;
      return *this;
    }

    const_iterator operator--(int) {
	  const_iterator tmp(*this);
      --*this;
      return tmp;
    }
  	const_iterator & operator--() {
	  if (ptr == cont->head->next)
	    throw index_out_of_bound();
      ptr = ptr->prev;
      return *this;
    }

    const value_type & operator*() const {
      return ptr->value;
    }

    bool operator==(const iterator &rhs) const {
      return ptr == rhs.ptr;
    }
    bool operator==(const const_iterator &rhs) const {
      return ptr == rhs.ptr;
    }

    bool operator!=(const iterator &rhs) const {
      return ptr != rhs.ptr;
    }
    bool operator!=(const const_iterator &rhs) const {
	  return ptr != rhs.ptr;
    }

    const value_type* operator->() const noexcept {
      return &ptr->value;
    }
  };

  linked_hashmap() :
      head(static_cast<Node*>(operator new(sizeof(Node)))),
      tail(static_cast<Node*>(operator new(sizeof(Node)))),
      buckets(new Node*[16]()),
      _size(0),
      bucket_count(16) {
    head->next = tail;
    tail->prev = head;
  }
  linked_hashmap(const linked_hashmap &other) :
      head(static_cast<Node*>(operator new(sizeof(Node)))),
      tail(static_cast<Node*>(operator new(sizeof(Node)))),
      buckets(new Node*[other.bucket_count]()),
      _size(other._size),
      bucket_count(other.bucket_count) {
    Node *cur_prev = head,
         *other_cur = other.head->next;
    for (size_t i = 0; i < _size; ++i) {
      Node *cur = new Node(other_cur->value);
      cur->prev = cur_prev;
      cur_prev->next = cur;
      size_t index = hasher(cur->value.first) % bucket_count;
      cur->hash_next = buckets[index];
      if (cur->hash_next != nullptr)
        cur->hash_next->hash_prev = cur;
      buckets[index] = cur;
      cur_prev = cur;
      other_cur = other_cur->next;
    }
    cur_prev->next = tail;
    tail->prev = cur_prev;
  }

  linked_hashmap & operator=(const linked_hashmap &other) {
    if (this == &other)
      return *this;
    Node *cur = head->next;
    while (cur != tail) {
	    Node *cur_next = cur->next;
      delete cur;
      cur = cur_next;
    }
    delete [] buckets;
    buckets = new Node*[other.bucket_count]();
  	_size = other._size;
    bucket_count = other.bucket_count;
  	Node *cur_prev = head,
         *other_cur = other.head->next;
    cur = head;
    for (size_t i = 0; i < _size; ++i) {
      cur = new Node(other_cur->value);
      cur->prev = cur_prev;
      cur_prev->next = cur;
      size_t index = hasher(cur->value.first) % bucket_count;
      cur->hash_next = buckets[index];
      if (cur->hash_next != nullptr)
        cur->hash_next->hash_prev = cur;
      buckets[index] = cur;
      cur_prev = cur;
      other_cur = other_cur->next;
  	}
  	cur->next = tail;
    tail->prev = cur;
    return *this;
  }

  ~linked_hashmap() {
    Node *cur = head->next;
    while (cur != tail) {
      Node *next = cur->next;
      delete cur;
      cur = next;
    }
    delete [] buckets;
    ::operator delete(head);
    ::operator delete(tail);
  }

  T & at(const Key &key) {
    size_t index = hasher(key) % bucket_count;
    Node *cur = buckets[index];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return cur->value.second;
      cur = cur->hash_next;
    }
    throw index_out_of_bound();
  }
  const T & at(const Key &key) const {
    size_t index = hasher(key) % bucket_count;
    const Node *cur = buckets[index];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return cur->value.second;
      cur = cur->hash_next;
    }
    throw index_out_of_bound();
  }

  T & operator[](const Key &key) {
    size_t index = hasher(key) % bucket_count;
    Node *cur = buckets[index];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return cur->value.second;
      cur = cur->hash_next;
    }
    cur = new Node(value_type(key, T()));
    cur->prev = tail->prev;
    cur->next = tail;
    cur->prev->next = cur;
    tail->prev = cur;
    cur->hash_next = buckets[index];
    if (cur->hash_next != nullptr)
      cur->hash_next->hash_prev = cur;
    buckets[index] = cur;
    ++_size;
    if (_size * 4 > bucket_count * 3)
      rehash(bucket_count * 2);
    else if (_size * 8 < bucket_count && bucket_count > 64)
      rehash(bucket_count / 2);
    return cur->value.second;
  }

  const T & operator[](const Key &key) const {
    size_t index = hasher(key) % bucket_count;
    const Node *cur = buckets[index];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return cur->value.second;
      cur = cur->hash_next;
    }
    throw index_out_of_bound();
  }

  iterator begin() {
	return iterator(head->next, this);
  }
  const_iterator cbegin() const {
	return const_iterator(head->next, this);
  }

  iterator end() {
	return iterator(tail, this);
  }
  const_iterator cend() const {
	return const_iterator(tail, this);
  }

  bool empty() const {
	return _size == 0;
  }

  size_t size() const {
    return _size;
  }

  void clear() {
    Node *cur = head->next;
    while (cur != tail) {
      Node *tmp = cur;
      cur = cur->next;
      delete tmp;
    }
    head->next = tail;
    tail->prev = head;
    delete [] buckets;
    buckets = new Node*[16]();
    _size = 0;
    bucket_count = 16;
  }

  pair<iterator, bool> insert(const value_type &value) {
    size_t index = hasher(value.first) % bucket_count;
    const Key &key = value.first;
    Node *cur = buckets[index];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return pair(iterator(cur, this), 0);
      cur = cur->hash_next;
    }
    cur = new Node(value);
    cur->prev = tail->prev;
    cur->next = tail;
    cur->prev->next = cur;
    tail->prev = cur;
    cur->hash_next = buckets[index];
    if (cur->hash_next != nullptr)
      cur->hash_next->hash_prev = cur;
    buckets[index] = cur;
    ++_size;
    // if (_size * 4 > bucket_count * 3)
    //   rehash(bucket_count * 2);
    // else if (_size * 8 < bucket_count && bucket_count > 64)
    //   rehash(bucket_count / 2);
    return pair(iterator(cur, this), 1);
  }

  void erase(iterator pos) {
    if (pos.cont != this || pos.ptr == tail)
      throw invalid_iterator();
    pos.ptr->prev->next = pos.ptr->next;
    pos.ptr->next->prev = pos.ptr->prev;
    if (pos.ptr->hash_prev != nullptr)
      pos.ptr->hash_prev->hash_next = pos.ptr->hash_next;
    else
      buckets[hasher(pos->first) % bucket_count] = pos.ptr->hash_next;
    if (pos.ptr->hash_next != nullptr)
      pos.ptr->hash_next->hash_prev = pos.ptr->hash_prev;
    delete pos.ptr;
    --_size;
  }

  size_t count(const Key &key) const {
    Node *cur = buckets[hasher(key) % bucket_count];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return 1;
      cur = cur->hash_next;
    }
    return 0;
  }

  iterator find(const Key &key) {
    Node *cur = buckets[hasher(key) % bucket_count];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return iterator(cur, this);
      cur = cur->hash_next;
    }
    return end();
  }
	const_iterator find(const Key &key) const {
    const Node *cur = buckets[hasher(key) % bucket_count];
    while (cur != nullptr) {
      if (equal(key, cur->value.first))
        return const_iterator(cur, this);
      cur = cur->hash_next;
    }
    return cend();
  }
};

}

#endif