#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Date
{
private:
    int _year;
    int _month;
    int _day;
public:
    //构造函数
    Date(): _year(1900), _month(1), _day(1) {}
    
    Date(const int y, const int m, const int d) : _year(y), _month(m), _day(d) {
        if (!isValid(y, m, d)) _year = 1900, _month = 1, _day = 1;
    }
    //判断是否为闰年
    static bool isLeapYear(const int y) {
        return y % 4 == 0 && y != 1900;
    }
    //一个日期加上一个天数
    Date operator+(const int off) const {
        int newoff = _day + off - month_days[_month] - (_month == 2 && isLeapYear(_year)) - 1;
        if (newoff < 0) {
            return Date(_year, _month, _day + off);
        }
        if (_month < 12) {
            return Date(_year, _month + 1, 1) + newoff;
        }
        return Date(_year + 1, 1, 1) + newoff;
    }
    //一个日期减去一个天数
    Date operator-(const int off) const {
        int newoff = off - _day;
        if (newoff < 0) {
            return Date(_year, _month, -newoff);
        }
        if (_month > 1) {
            int newmonth = _month - 1;
            return Date(_year, newmonth, month_days[newmonth] + (newmonth == 2 && isLeapYear(_year))).operator-(newoff);
        }
        return Date(_year - 1, 12, 31).operator-(newoff);
    }
    //前置++
    Date& operator++() {
        if (_day < month_days[_month] + (_month == 2 && isLeapYear(_year))) {
            ++_day;
            return *this;
        }
        _day = 1;
        if (_month < 12) {
            ++_month;
            return *this;
        }
        _month = 1;
        ++_year;
        return *this;
    }
    //后置++
    Date operator++(int) {
        Date temp = *this;
        ++*this;
        return temp;
    }
    //前置--
    Date& operator--() {
        if (_day > 1) {
          --_day;
          return *this;
        }
        if (_month > 1) {
            --_month;
            _day = month_days[_month] + (_month == 2 && isLeapYear(_year));
            return *this;
        }
        --_year;
        _month = 12;
        _day = 31;
        return *this;
    }
    //后置--
    Date operator--(int) {
        Date temp = *this;
        --*this;
        return temp;
    }
    //<重载
    bool operator<(const Date &other) const {
        if (_year < other._year) return true;
        if (_year > other._year) return !(other < *this);
        if (_month < other._month) return true;
        if (_month > other._month) return !(other < *this);
        return _day < other._day;
    }
    //日期-日期
    int operator-(const Date &other) const {
        if (_year < other._year) {
            return other.diff_curr_year() - diff_curr_year() + 365 * (other._year - _year)
                + (other._year - 1) / 4 - (_year - 1) / 4 - (_year == 1900);
        }
        if (_year > other._year) {
            return other - *this;
        }
        if (_month < other._month) {
            return other._day - _day + diff_between_month(_month, other._month)
                + (_month < 3 && other._month > 2 && isLeapYear(_year));
        }
        if (_month > other._month) {
            return other - *this;
        }
        int diff = _day - other._day;
        return diff < -0 ? -diff : diff;
    }
    //重载输出运算符
    friend ostream& operator<<(ostream& os, const Date& date) {
        os << date._year << '-' << date._month << '-' << date._day;
        return os;
    }
    //以上仅为提示，不代表你需要完成所有，你也可以添加其他需要的函数。
    static bool isValid(int y, int m, int d) {
        if (m < 1 || m > 12 || d < 1 || d > month_days[m] + (m == 2 && isLeapYear(y))) {
            // std::cout << y << '-' << m << '-' << d << '\n';
            return false;
        }
        return true;
    }

    int diff_curr_year() const {
        int diff = _day + (_month > 2 && isLeapYear(_year));
        for (int i = 1; i < _month; ++i) diff += month_days[i];
        return diff;
    }

    static int diff_between_month(int m1, int m2) {
        int diff = 0;
        for (int i = m1; i < m2; ++i) diff += month_days[i];
        return diff;
    }
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}
int main()
{
    Test();
    return 0;
}