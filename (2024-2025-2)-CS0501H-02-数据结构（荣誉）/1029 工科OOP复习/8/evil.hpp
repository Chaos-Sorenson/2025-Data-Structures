#ifndef EVIL_HPP
#define EVIL_HPP

#include <iostream>
using namespace std;

class Evil{
private:
    int st, ed, val;
    int *data;

public:

    //构造函数
    Evil() : st(0), ed(0), val(0), data(new int[1]) {
        data[0] = 0;
    }

    Evil(int s, int e, int v) : st(s), ed(e), val(v), data(new int[e - s + 1]) {
        for (int i = 0; i < e - s + 1; ++i) data[i] = 0;
    }

    Evil(const Evil& o) : st(o.st), ed(o.ed), val(o.val) {
        data = new int[ed - st + 1];
        for (int i = 0; i < ed - st + 1; ++i) data[i] = o.data[i];
    }

    Evil(Evil&& o) : st(o.st), ed(o.ed), val(o.val), data(o.data) {
        o.data = nullptr;
    }
    //下标运算符重载
    int& operator[](const int& i) {
        return data[(i < st || i > ed) ? 0 : i - st];
    }
    //赋值运算符重载
    Evil& operator=(const Evil& o) {
        if (this == &o) return *this;
        st = o.st;
        ed = o.ed;
        val = o.val;
        delete[] data;
        data = new int[ed - st + 1];
        for (int i = 0; i < ed - st + 1; ++i) data[i] = o.data[i];
        return *this;
    }

    Evil& operator=(Evil&& o) {
        st = o.st;
        ed = o.ed;
        val = o.val;
        delete[] data;
        data = o.data;
        o.data = nullptr;
    }
    //前缀++重载
    Evil& operator++() {
        ++val;
        return *this;
    }
    //后缀++重载
    Evil operator++(int) {
        Evil tmp = *this;
        ++val;
        return tmp;
    }
    //输出重载
    friend ostream& operator<<(ostream& os, const Evil& o) {
        os << o.val << ' ';
        for (int i = 0; i < o.ed - o.st + 1; ++i) os << o.data[i] << ' ';
        os << '\n';
        return os;
    }
    //析构函数
    ~Evil() {
        delete[] data;
    }

    void Print(){
        cout << val << " ";
        for(int i = 0;i < ed-st+1;++i)
            cout << data[i] <<" ";
        cout << endl;
    }
};

#endif//EVIL_HPP