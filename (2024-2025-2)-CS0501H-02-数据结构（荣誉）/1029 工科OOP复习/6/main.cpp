#ifndef SRC_HPP
#define SRC_HPP
namespace sjtu {
    template <class T>
    void sort(T* first, T* last){
        // TODO
        // O(nlogn)
        int n = last - first, i, j, k;
        T tmp;
        //建堆，大顶堆
        for (i = n / 2 - 1; i >= 0; --i) {
            j = i;
            //下滤
            while (2 * j + 1 < n) {
                k = 2 * j + 1;
                if (k + 1 < n) if (first[k] < first[k + 1]) ++k;
                if (first[j] < first[k]) {
                    tmp = first[j];
                    first[j] = first[k];
                    first[k] = tmp;
                    j = k;
                } else break;
            }
        }
        //堆排序，小序堆
        while (n > 1) {
            tmp = first[--n];
            first[n] = *first;
            *first = tmp;
            j = 0;
            while (2 * j + 1 < n) {
                k = 2 * j + 1;
                if (k + 1 < n) if (first[k] < first[k + 1]) ++k;
                if (first[j] < first[k]) {
                    tmp = first[j];
                    first[j] = first[k];
                    first[k] = tmp;
                    j = k;
                } else break;
            }
        }
    }

    template <class T>
    T* lower_bound(T* first, T* last, const T& value) {
        // TODO
        // O(logn)
        int lh = 0, rh = last - first - 1, m;
        if (first[rh] < value) return last;
        if (!(first[lh] < value)) return first;
        while (lh + 1 < rh) {
            m = (lh + rh) / 2;
            if (first[m] < value) lh = m;
            else rh = m;
        }
        return first + rh;
    }

    template <class T>
    T* upper_bound(T* first, T* last, const T& value) {
        // TODO
        // O(logn)
            int lh = 0, rh = last - first - 1, m;
            if (!(value < first[rh])) return last;
            if (value < first[lh]) return first;
            while (lh + 1 < rh) {
                m = (lh + rh) / 2;
                if (value < first[m]) rh = m;
                else lh = m;
            }
            return first + rh;
    }
}  // namespace sjtu
#endif