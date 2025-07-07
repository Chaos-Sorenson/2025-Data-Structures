#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>

namespace sjtu
{
template<typename T>
class vector
{
public:
  T* data;
  size_t _begin;
  size_t _end;
  size_t _capacity;
  static const int sizeofT = sizeof(T);

  class const_iterator;

  class iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;

    const vector* container;
    T* ptr;

    iterator() : container(nullptr), ptr(nullptr) {  }

    iterator(const vector* _container, const T* _ptr) : container(_container), ptr(const_cast<T*>(_ptr)) {  }

    iterator(const iterator& _it) : container(_it.container), ptr(_it.ptr) {  }

    explicit iterator(const const_iterator& _it) : container(_it.container), ptr(const_cast<T*>(_it.ptr)) {  }

    iterator& operator=(const iterator& _it) {
      if (this != &_it) {
        container = _it.container;
        ptr = _it.ptr;
      } return *this;
    }

    iterator& operator=(const const_iterator& _it) {
      container = _it.container;
      ptr = const_cast<T*>(_it.ptr);
      return *this;
    }

    iterator operator+(const int &n) const {
      iterator tmp = *this;
      tmp.ptr += n;
      return tmp;
    }

    iterator operator-(const int &n) const {
      iterator tmp = *this;
      tmp.ptr -= n;
      return tmp;
    }

    difference_type operator-(const iterator &rhs) const {
      if (container != rhs.container) throw invalid_iterator();
      return ptr - rhs.ptr;
    }

    difference_type operator-(const const_iterator &rhs) const {
      if (container != rhs.container) throw invalid_iterator();
      return ptr - rhs.ptr;
    }

    iterator& operator+=(const int &n) {
      ptr += n;
      return *this;
    }

    iterator& operator-=(const int &n) {
      ptr -= n;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++ptr;
      return tmp;
    }

    iterator& operator++() {
      ++ptr;
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      --ptr;
      return tmp;
    }

    iterator& operator--() {
      --ptr;
      return *this;
    }

    T& operator*() const { return *ptr; }

    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }

    bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }
  };

  class const_iterator {
  public:
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using iterator_category = std::output_iterator_tag;

    const vector* container;
    const T* ptr;

    const_iterator() : container(nullptr), ptr(nullptr) {  }

    const_iterator(const vector* _container, const T* _ptr) : container(_container), ptr(_ptr) {  }

    const_iterator(const const_iterator& _it) : container(_it.container), ptr(_it.ptr) {  }

    explicit const_iterator(const iterator& _it) : container(_it.container), ptr(const_cast<const T*>(_it.ptr)) {  }

    const_iterator& operator=(const const_iterator& _it) {
      if (this != &_it) {
        container = _it.container;
        ptr = _it.ptr;
      } return *this;
    }

    const_iterator& operator=(const iterator& _it) {
      container = _it.container;
      ptr = const_cast<const T*>(_it.ptr);
      return *this;
    }

    iterator operator+(const int n) const {
      iterator tmp = *this;
      tmp.ptr += n;
      return tmp;
    }

    iterator operator-(const int n) const {
      iterator tmp = *this;
      tmp.ptr -= n;
      return tmp;
    }

    difference_type operator-(const const_iterator &rhs) const {
      if (container != rhs.container) throw invalid_iterator();
      return ptr - rhs.ptr;
    }

    difference_type operator-(const iterator &rhs) const {
      if (container != rhs.container) throw invalid_iterator();
      return ptr - rhs.ptr;
    }

    const_iterator& operator+=(const int n) {
      ptr += n;
      return *this;
    }

    const_iterator& operator-=(const int n) {
      ptr -= n;
      return *this;
    }

    const_iterator& operator++() {
      ++ptr;
      return *this;
    }

    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++ptr;
      return tmp;
    }

    const_iterator& operator--() {
      --ptr;
      return *this;
    }

    const_iterator operator--(int) {
      const_iterator tmp = *this;
     --ptr;
      return tmp;
    }

    const T& operator*() const { return *ptr; }

    bool operator==(const const_iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; }

    bool operator!=(const const_iterator &rhs) const { return ptr != rhs.ptr; }

    bool operator!=(const iterator &rhs) const { return ptr != rhs.ptr; }
  };

    vector() : data(static_cast<T*>(operator new(sizeofT))), _begin(0), _end(0), _capacity(0) {  }

    vector(const vector &other) : _begin(other._begin), _end(other._end), _capacity(other._capacity) {
      data = static_cast<T*>(operator new(sizeofT * (_capacity + 1)));
      for (size_t i = _begin; i < _end; ++i) new (data + i) T(other.data[i]);
    }

    ~vector() {
      for (size_t i = _begin; i < _end; ++i) data[i].~T();
      ::operator delete(data);
    }

    vector &operator=(const vector &other) {
      if (this != &other) {
        for (size_t i = _begin; i < _end; ++i) data[i].~T();
        ::operator delete(data);
        _begin = other._begin;
        _end = other._end;
        _capacity = other._capacity;
        data = static_cast<T*>(::operator new(sizeofT * (_capacity + 1)));
        for (size_t i = _begin; i < _end; ++i) new (data + i) T(other.data[i]);
      } return *this;
    }

    vector &operator=(vector &&other) noexcept {
      for (size_t i = _begin; i < _end; ++i) data[i].~T();
      ::operator delete(data);
      _begin = other._begin;
      _end = other._end;
      _capacity = other._capacity;
      data = other.data;
      other.data = nullptr;
      return *this;
    }

    T & at(const size_t &pos) {
      if (pos < 0 || pos >= size()) throw index_out_of_bound();
      return data[_begin + pos];
    }

    const T & at(const size_t &pos) const {
      if (pos < 0 || pos >= size()) throw index_out_of_bound();
      return data[_begin + pos];
    }

    T & operator[](const size_t &pos) {
      if (pos < 0 || pos >= size()) throw index_out_of_bound();
      return data[_begin + pos];
    }

    const T & operator[](const size_t &pos) const {
      if (pos < 0 || pos >= size()) throw index_out_of_bound();
      return data[_begin + pos];
    }

    const T & front() const {
      if (_begin == _end) throw container_is_empty();
      return data[_begin];
    }

    const T & back() const {
      if (_begin == _end) throw container_is_empty();
      return data[_end - 1];
    }

    iterator begin() { return iterator(this, data + _begin); }

    const_iterator begin() const { return const_iterator(this, const_cast<const T*>(data + _begin)); }

    const_iterator cbegin() const { return const_iterator(this, const_cast<const T*>(data + _begin)); }

    iterator end() { return iterator(this, data + _end); }

    const_iterator end() const { return const_iterator(this, const_cast<const T*>(data + _end)); }

    const_iterator cend() const { return const_iterator(this, const_cast<const T*>(data + _end)); }

    bool empty() const { return _begin == _end; }

    size_t size() const { return _end - _begin; }

    void clear() {
      for (size_t i = _begin; i < _end; ++i) data[i].~T();
      _end = _begin = _capacity >> 1;
    }

    iterator insert(iterator pos, const T &value) { return insert(pos - begin(), value); }

    iterator insert(const size_t &ind, const T &value) {
      if (ind > size()) throw index_out_of_bound();
      if (_capacity == 0){
        ::operator delete(data);
        _begin = 1, _end = 2, _capacity = 3;
        data = static_cast<T*>(::operator new(sizeofT << 2));
        new (data + 1) T(value);
        return iterator(this, data + 1);
      } if (ind > _end - _begin >> 1) {
        if (_end < _capacity) return oldforward(ind, value);
        if (_begin > _capacity / 3) return oldbackward(ind, value);
        return newforward(ind, value);
        } if (_begin > 0) return oldbackward(ind, value);
      if (_end < (_capacity << 1) / 3) return oldforward(ind, value);
      return newbackward(ind, value);
    }

    iterator newforward(const size_t &ind, const T &value) {
      size_t newbegin = _begin, newend = _end + 1, newcapacity = _capacity + 1 << 1;
      T* newdata = static_cast<T*>(::operator new(sizeofT * (newcapacity + 1)));
      for (size_t i = 0; i < ind; ++i) {
        new (newdata + newbegin + i) T(data[_begin + i]);
        data[_begin + i].~T();
      } new (newdata + newbegin + ind) T(value);
      for (size_t i = size(); i > ind; --i) {
        new (newdata + newbegin + i) T(data[_begin + i - 1]);
        data[_begin + i - 1].~T();
      } ::operator delete(data);
      data = newdata, _begin = newbegin, _end = newend, _capacity = newcapacity;
      return iterator(this, data + _begin + ind);
    }

    iterator oldforward(const size_t &ind, const T &value) {
      if (ind == size()) {
        new (data + _end) T(value);
        ++_end;
        return iterator(this, data + _end - 1);
      } new (data + _end) T(data[_end - 1]);
      for (size_t i = size() - 1; i > ind; --i) data[_begin + i] = data[_begin + i - 1];
      data[_begin + ind] = value;
      ++_end;
      return iterator(this, data + _begin + ind);
    }

    iterator newbackward(const size_t &ind, const T &value) {
      size_t newbegin = _capacity + 1 + _begin, newend = _capacity + _end + 2, newcapacity = _capacity + 1 << 1;
      T* newdata = static_cast<T*>(::operator new(sizeofT * (newcapacity + 1)));
      const size_t _size = size();
      for (size_t i = ind; i < _size; ++i) {
        new (newdata + newbegin + i + 1) T(data[_begin + i]);
        data[_begin + i].~T();
      } new (newdata + newbegin + ind) T(value);
      for (size_t i = 0; i < ind; --i) {
        new (newdata + newbegin + i) T(data[_begin + i]);
        data[_begin + i].~T();
      } ::operator delete(data);
      data = newdata, _begin = newbegin, _end = newend, _capacity = newcapacity;
      return iterator(this, data + _begin + ind);
    }

    iterator oldbackward(const size_t &ind, const T &value) {
      --_begin;
      if (ind == 0) {
        new (data + _begin) T(value);
        return iterator(this, data + _begin);
      } new (data + _begin) T(data[_begin + 1]);
      for (size_t i = 1; i < ind; ++i) data[_begin + i] = data[_begin + i + 1];
      data[_begin + ind] = value;
      return iterator(this, data + _begin + ind);
    }

    iterator erase(iterator pos) { return erase(pos - begin()); }

    iterator erase(const size_t &ind) {
      if (ind >= size()) throw index_out_of_bound();
      if (ind > _end - _begin >> 1) {
        const size_t _size = size();
        for (size_t i = ind + 1; i < _size; i++) data[_begin + i - 1] = data[_begin + i];
        data[_end - 1].~T();
        --_end;
        return iterator(this, data + ind);
      } for (size_t i = ind; i > 0; --i) data[_begin + i] = data[_begin + i - 1];
      data[_begin].~T();
      ++_begin;
      return iterator(this, data + _begin + ind);
    }

    void push_back(const T &value) {
      if (_end < _capacity) oldforward(size(), value);
      else if (_begin > _capacity/ 3) oldbackward(size(), value);
      else if (_capacity == 0) {
        ::operator delete(data);
        _begin = 1, _end = 2, _capacity = 3;
        data = static_cast<T*>(::operator new(sizeofT << 2));
        new (data + 1) T(value);
      } else newforward(size(), value);
    }

    void pop_back() {
      if (_begin == _end) throw container_is_empty();
      --_end;
      data[_end].~T();
    }
};

}

#endif