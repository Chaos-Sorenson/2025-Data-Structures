//
// Created by 1 on 25-2-23.
//

#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>

using namespace std;

#define USE_OS

class error : public std::exception {
private:
    std::string msg;

public:
    explicit error(const char *_msg_) : msg(_msg_) {}

    const char *toString() {
        return msg.c_str();
    }
};

template <typename _Ty>
class ArrayList {
private:
    int _size;
    _Ty* _data;

public:
    ArrayList(const _Ty* _Arr, const int& _Size) : _size(_Size) {
        if (_Size < 0) throw error("invalid length");
        _data = new _Ty[_size + 1];
        for (int i = 0; i < _Size; ++i) _data[i] = _Arr[i];
    }

    explicit ArrayList(const int& _Size) : _size(_Size) {
        if (_Size < 0) throw error("invalid length");
        _data = new _Ty[_size + 1];
    }

    ArrayList(const ArrayList& _Right) : _size(_Right._size), _data(new _Ty[_size + 1]) {
        for (int i = 0; i < _size; ++i) _data[i] = _Right[i];
    }

    ArrayList(ArrayList&& _Right) noexcept : _size(_Right._size), _data(_Right._data) {
        _Right._data = nullptr;
    }

    ~ArrayList() {
        delete[] _data;
    }

    int size() const {
        return _size;
    }

    _Ty& operator[](const int& _Off) {
        if (_Off < 0 || _Off > _size) throw error("index out of bound");
        return _data[_Off];
    }

    const _Ty& operator[](const int& _Off) const {
        if (_Off < 0 || _Off > _size) throw error("index out of bound");
        return _data[_Off];
    }

    ArrayList operator+(const ArrayList& _Right) const {
        ArrayList _Tmp(_size + _Right._size);
        for (int i = 0; i < _size; ++i) _Tmp[i] = _data[i];
        for (int i = 0; i < _Right._size; ++i) _Tmp[_size + i] = _Right[i];
        return _Tmp;
    }

    ArrayList& operator=(const ArrayList& _Right) {
        if (this == &_Right) return *this;

        _size = _Right._size;
        delete[] _data;
        _data = new _Ty[_size + 1];
        for (int i = 0; i < _size; ++i) _data[i] = _Right[i];
        return *this;
    }

    ArrayList& operator=(ArrayList&& _Right) {
        _size = _Right._size;
        delete[] _data;
        _data = _Right._data;
        _Right._data = nullptr;
        return *this;
    }

    bool operator==(const ArrayList& _Right) const {
        if (_size != _Right._size) return false;

        for (int i = 0; i < _size; ++i) if (_data[i] != _Right[i]) return false;
        return true;
    }

    bool operator!=(const ArrayList& _Right) const {
        return !(operator==(_Right));
    }

    friend ostream& operator<<(ostream& os, const ArrayList& _Right) {
        for (int i = 0; i < _Right._size; ++i) os << _Right[i] << ' ';
        return os;
    }

    friend void printList(ArrayList list) {
#ifdef USE_OS
        std::cout << list << "\n";
#else
        list.print();
        std::cout << "\n";
#endif
    }
};

#endif //FILE_H
