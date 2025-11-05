//
// Created by 1 on 25-2-23.
//

#ifndef FILE_H
#define FILE_H

#include <iostream>
using namespace std;

template <typename _Ty>
class LinkedList {
protected:
    struct _node {
        _Ty _data;
        _node * _next;
        _node * _prev;

        _node() : _next(nullptr), _prev(nullptr) {}

        _node(_Ty _Data, _node* _Prev) : _data(_Data), _next(nullptr), _prev(_Prev) {}

        _node(_Ty _Data, _node* _Next, _node* _Prev) : _data(_Data), _next(_Next), _prev(_Prev) {}
    };
    int _size;
    _node* _head;
    _node* _tail;

public:
    LinkedList() : _size(0), _head(new _node), _tail(new _node) {
        _head->_next = _tail;
        _tail->_prev = _head;
    }

    LinkedList(const LinkedList& _Right) : _size(_Right._size), _head(new _node) {
        _node* p = _head;
        _node* q = _Right._head;

        while ((q = q->_next) != _Right._tail) {
            p = new _node(q->_data, p);
            p->_prev->_next = p;
        }

        _tail = new _node;
        p ->_next = _tail;
        _tail->_prev = p;
    }

    virtual ~LinkedList() {
        _node* p = _head->_next;

        do {
            delete p->_prev;
            p->_prev = nullptr;
            p = p->_next;
        } while (p != nullptr);

        delete _tail;
    }

    void pushFront(const _Ty& _Data) {
        _node* p = new _node(_Data, _head->_next, _head);
        _head->_next = _head->_next->_prev = p;

        ++_size;
    }

    void pushBack(const _Ty& _Data) {
        _node* p = new _node(_Data, _tail, _tail->_prev);
        _tail->_prev = _tail->_prev->_next = p;

        ++_size;
    }

    _Ty popFront() {
        if (_size == 0) {
            return _Ty();
        }
        --_size;

        _node* p = _head->_next;
        _head->_next = p->_next;
        p->_next->_prev = _head;

        _Ty _Tmp = p->_data;
        delete p;
        p = nullptr;

        return _Tmp;
    }

    _Ty popBack() {
        if (_size == 0) {
            return _Ty();
        }
        --_size;

        _node* p = _tail->_prev;
        _tail->_prev = p->_prev;
        p->_prev->_next = _tail;

        _Ty _Tmp = p->_data;
        delete p;
        p = nullptr;

        return _Tmp;
    }

    int size() const {
        return _size;
    }

    void print() {
        _node* p = _head->_next;
        while (p != _tail) {
            cout << p->_data << " ";
            p = p->_next;
        }
        cout << '\n';
    }

    virtual const char* name() const {
        return nullptr;
    }

    virtual _Ty peak() const {
        return _Ty();
    }

    virtual _Ty pop() {
        return _Ty();
    }

    virtual void push(const _Ty& _Data) {
        return void();
    }
};

template <typename _Ty>
class Stack : public LinkedList<_Ty> {
public:
    virtual const char* name() const {
        return "Stack";
    }

    virtual _Ty peak() const {
        if (LinkedList<_Ty>::_size == 0) return _Ty();
        return LinkedList<_Ty>::_head->_next->_data;
    }

    virtual _Ty pop() {
        if (LinkedList<_Ty>::_size == 0) return _Ty();
        return LinkedList<_Ty>::popFront();
    }

    virtual void push(const _Ty& _Data) {
        LinkedList<_Ty>::pushFront(_Data);
    }
};

template <typename _Ty>
class Queue : public LinkedList<_Ty> {
public:
    virtual const char* name() const {
        return "Queue";
    }

    virtual _Ty peak() const {
        if (LinkedList<_Ty>::_size == 0) return _Ty();
        return LinkedList<_Ty>::_head->_next->_data;
    }

    virtual _Ty pop() {
        if (LinkedList<_Ty>::_size == 0) return _Ty();
        return LinkedList<_Ty>::popFront();
    }

    virtual void push(const _Ty& _Data) {
        LinkedList<_Ty>::pushBack(_Data);
    }
};
#endif //FILE_H
