#ifndef SJTU_PRIORITY_QUEUE_HPP
#define SJTU_PRIORITY_QUEUE_HPP

#include <cstddef>
#include <functional>
#include "exceptions.hpp"

namespace sjtu {

template<typename T, class Compare = std::less<T>>
class priority_queue {
public:
  static const size_t sizeofT = sizeof(T);
  struct node {
    T *value;
    node *child, *sibling;

    explicit node(const T &e) : value{static_cast<T*>(operator new(sizeofT))}, child{nullptr}, sibling{nullptr} {
  	  new (value) T(e);
    }

    node(const node &other) : value{static_cast<T*>(operator new(sizeofT))}, child{nullptr}, sibling{nullptr} {
      new (value) T(*other.value);
      if (other.child) child = new node(*other.child);
      if (other.sibling) sibling = new node(*other.sibling);
    }

    ~node() {
      value->~T();
      ::operator delete(value);
      if (child) {
        delete child;
      	child = nullptr;
      }
  	  if (sibling) {
  	  	delete sibling;
  	  	sibling = nullptr;
  	  }
    }
  } *root[32];
  Compare comp;

	/**
	 * @brief default constructor
	 */
    priority_queue() {
      for (auto & i : root) i = nullptr;
    }

	/**
	 * @brief copy constructor
	 * @param other the priority_queue to be copied
	 */
    priority_queue(const priority_queue &other) {
      for (int i = 0; i < 32; ++i) root[i] = other.root[i] ? new node(*other.root[i]) : nullptr;
    }

	/**
	 * @brief deconstructor
	 */
    ~priority_queue() {
      for (auto & i : root) if (i) {
        delete i;
      	i = nullptr;
      }
    }

	/**
	 * @brief Assignment operator
	 * @param other the priority_queue to be assigned from
	 * @return a reference to this priority_queue after assignment
	 */
    priority_queue &operator=(const priority_queue &other) {
      if (this != &other) {
        for (auto & i : root) if (i) {
          delete i;
          i = nullptr;
        }
        for (int i = 0; i < 32; ++i) if (other.root[i]) root[i] = new node(*other.root[i]);
      }
      return *this;
    }

	/**
	 * @brief get the top element of the priority queue.
	 * @return a reference of the top element.
	 * @throws container_is_empty if empty() returns true
	 */
	const T & top() const {
      int i = 0;
      for (; i < 32; ++i) if (root[i]) break;
      if (i == 32) throw container_is_empty();
      T *max_ptr = root[i]->value;
      ++i;
      for (; i < 32; ++i) if (root[i]) {
        try {
          if(comp(*max_ptr, *root[i]->value)) max_ptr = root[i]->value;
        } catch (...) { throw; }
      }
      return *max_ptr;
    }

	/**
	 * @brief push new element to the priority queue.
	 * @param e the element to be pushed
	 */
    void push(const T &e) {
      try { comp(e, e); } catch (...) { throw; }
      T carry_val = e;
      for (auto & i : root) {
        if (!i) break;
      	try {
          if (comp(carry_val, *i->value)) carry_val = *i->value;
        } catch (...) { throw; }
      }

      node *carry = new node(e);
      for (auto & i : root) {
      	if (!i) {
      	  i = carry;
      	  break;
      	}
      	if (comp(*carry->value, *i->value)) std::swap(i, carry);
      	i->sibling = carry->child, carry->child = i, i = nullptr;
      }
    }

	/**
	 * @brief delete the top element from the priority queue.
	 * @throws container_is_empty if empty() returns true
	 */
	void pop() {
      int i = 0;
      for (; i < 32; ++i) if (root[i]) break;
      if (i == 32) throw container_is_empty();

      T max = *root[i]->value;
      int max_ind = i;
      for (++i; i < 32; ++i) if (root[i]) try {
          if (comp(max, *root[i]->value)) max = *root[i]->value, max_ind = i;
        } catch (...) { throw; }

      if (!max_ind) {
        delete root[0], root[0] = nullptr;
      	return;
      }

      node *tmp[max_ind];
      tmp[0] = root[max_ind]->child;
      for (i = 1; i < max_ind; ++i) tmp[i] = tmp[i - 1]->sibling, tmp[i - 1]->sibling = nullptr;

      T *carry_val_ptr = nullptr;
      for (i = 0; i < max_ind; ++i) {
	    if (!carry_val_ptr) {
          if (root[i]) try {
            carry_val_ptr = comp(*tmp[max_ind - 1 - i]->value, *root[i]->value) ? root[i]->value : tmp[max_ind - 1 - i]->value;
          } catch (...) { throw; }
	    } else try {
          if (comp(*carry_val_ptr, *tmp[max_ind - 1 - i]->value)) carry_val_ptr = tmp[max_ind - 1 - i]->value;
        } catch (...) { throw; }
      }

      root[max_ind]->child = nullptr;
      delete root[max_ind];
      root[max_ind] = nullptr;
      node *carry = nullptr;
      for (i = 0; i < max_ind; ++i) {
	    if (!carry) {
		  if (root[i]) {
		    if (comp(*tmp[max_ind - 1 - i]->value, *root[i]->value)) std::swap(root[i], tmp[max_ind - 1 - i]);
		  	carry = tmp[max_ind - 1 - i], root[i]->sibling = carry->child, carry->child = root[i], root[i] = nullptr;
		  } else root[i] = tmp[max_ind - 1 - i];
	    } else {
      	  if (comp(*carry->value, *tmp[max_ind - 1 - i]->value)) std::swap(tmp[max_ind - 1 - i], carry);
      	  tmp[max_ind - 1 - i]->sibling = carry->child, carry->child = tmp[max_ind - 1 - i];
      	}
      }
      root[max_ind] = carry;
    }

	/**
	 * @brief return the number of elements in the priority queue.
	 * @return the number of elements.
	 */
	size_t size() const {
      size_t s = 0, p = 1;
      for (auto & i : root) {
        if (i) s += p;
        p <<= 1;
      }
      return s;
    }

	/**
	 * @brief check if the container is empty.
	 * @return true if it is empty, false otherwise.
	 */
	bool empty() const {
      for (auto & i : root) if (i) return false;
      return true;
    }

	/**
	 * @brief merge another priority_queue into this one.
	 * The other priority_queue will be cleared after merging.
	 * The complexity is at most O(logn).
	 * @param other the priority_queue to be merged.
	 */
	void merge(priority_queue &other) {
	  T *carry_val_ptr = nullptr;
      for (int i = 0; i < 32; ++i) {
	    if (!carry_val_ptr) if (root[i] && other.root[i]) try {
          carry_val_ptr = comp(*other.root[i]->value, *root[i]->value) ? root[i]->value : other.root[i]->value;
        } catch (...) { throw; } else if (other.root[i]) try {
	      if (comp(*carry_val_ptr, *other.root[i]->value)) carry_val_ptr = other.root[i]->value;
	    } catch (...) { throw; } else if (root[i]) try {
          if (comp(*carry_val_ptr, *root[i]->value)) carry_val_ptr = root[i]->value;
      	} catch (...) { throw; } else carry_val_ptr = nullptr;
      }
      node *carry = nullptr;
      for (int i = 0; i < 32; ++i) {
        if (!carry) {
          if (root[i] && other.root[i]) {
            if (comp(*other.root[i]->value, *root[i]->value)) std::swap(root[i], other.root[i]);
          	carry = other.root[i], root[i]->sibling = carry->child, carry->child = root[i], root[i] = nullptr;
          } else if (other.root[i]) root[i] = other.root[i];
        } else if (other.root[i]) {
          if (comp(*carry->value, *other.root[i]->value)) std::swap(other.root[i], carry);
          other.root[i]->sibling = carry->child, carry->child = other.root[i];
      	} else if (root[i]) {
          if (comp(*carry->value, *root[i]->value)) std::swap(root[i], carry);
          root[i]->sibling = carry->child, carry->child = root[i], root[i] = nullptr;
      	} else root[i] = carry, carry = nullptr;
      }
      for (auto & i : other.root) i = nullptr;
    }
};

}

#endif