#pragma once
#include <bits/stdc++.h>
using namespace std;

extern unsigned long long g_charCmp;

inline int cmpStrings(const string &a, const string &b) {
    size_t n = min(a.size(), b.size());
    for (size_t i = 0; i < n; ++i) {
        ++g_charCmp;
        if (a[i] != b[i])
            return (unsigned char)a[i] < (unsigned char)b[i] ? -1 : 1;
    }
    if (a.size() == b.size()) return 0;
    return a.size() < b.size() ? -1 : 1;
}

inline pair<int, int> cmpFrom(const string &x, const string &y, int start) {
    int i = start, lx = (int)x.size(), ly = (int)y.size();
    while (i < lx && i < ly) {
        ++g_charCmp;
        if (x[i] != y[i])
            return {i, (unsigned char)x[i] < (unsigned char)y[i] ? -1 : 1};
        ++i;
    }
    if (lx == ly) return {i, 0};
    return {i, lx < ly ? -1 : 1};
}

inline int charAt(const string &s, int d) {
    ++g_charCmp;
    return d < (int)s.size() ? (unsigned char)s[d] : -1;
}

inline void stdQuickSortRec(vector<string> &a, int lo, int hi) {
    while (lo < hi) {
        swap(a[lo], a[lo + (hi - lo) / 2]);
        const string pivot = a[lo];
        int lt = lo;
        for (int i = lo + 1; i <= hi; ++i)
            if (cmpStrings(a[i], pivot) < 0) swap(a[++lt], a[i]);
        swap(a[lo], a[lt]);
        if (lt - lo < hi - lt) { stdQuickSortRec(a, lo, lt - 1); lo = lt + 1; }
        else                   { stdQuickSortRec(a, lt + 1, hi); hi = lt - 1; }
    }
}

inline void standardQuickSort(vector<string> &a) {
    if (a.size() > 1) stdQuickSortRec(a, 0, (int)a.size() - 1);
}

inline void stdMergeSortRec(vector<string> &a, vector<string> &buf, int l, int r) {
    if (r - l < 2) return;
    int m = (l + r) / 2;
    stdMergeSortRec(a, buf, l, m);
    stdMergeSortRec(a, buf, m, r);
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (cmpStrings(a[i], a[j]) <= 0) buf[k++] = a[i++];
        else                            buf[k++] = a[j++];
    }
    while (i < m) buf[k++] = a[i++];
    while (j < r) buf[k++] = a[j++];
    for (int t = l; t < r; ++t) a[t] = buf[t];
}

inline void standardMergeSort(vector<string> &a) {
    vector<string> buf(a.size());
    stdMergeSortRec(a, buf, 0, (int)a.size());
}

inline void stringQuickSortRec(vector<string> &a, int lo, int hi, int d) {
    if (hi <= lo) return;
    swap(a[lo], a[lo + (hi - lo) / 2]);
    int lt = lo, gt = hi, i = lo + 1;
    int v = charAt(a[lo], d);
    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v)      swap(a[lt++], a[i++]);
        else if (t > v) swap(a[i], a[gt--]);
        else            ++i;
    }
    stringQuickSortRec(a, lo, lt - 1, d);
    if (v >= 0) stringQuickSortRec(a, lt, gt, d + 1);
    stringQuickSortRec(a, gt + 1, hi, d);
}

inline void stringQuickSort(vector<string> &a) {
    if (a.size() > 1) stringQuickSortRec(a, 0, (int)a.size() - 1, 0);
}

inline void lcpMergeRange(const vector<string> &a, const vector<int> &ah,
                          int l, int mid, int r,
                          vector<string> &b, vector<int> &bh) {
    int i = l, j = mid, k = l;
    auto cf = cmpFrom(a[l], a[mid], 0);
    int m = cf.first, cmp = cf.second;
    int lastRun = 0;
    int mEmit = 0;
    while (i < mid && j < r) {
        if (cmp <= 0) {
            b[k] = a[i];
            bh[k++] = (lastRun == 1) ? ah[i] : (lastRun == 0 ? 0 : mEmit);
            mEmit = m; lastRun = 1; ++i;
            if (i < mid) {
                int hl = ah[i];
                if (hl > m)      cmp = -1;
                else if (hl < m) { m = hl; cmp = 1; }
                else { auto c = cmpFrom(a[i], a[j], m); m = c.first; cmp = c.second; }
            }
        } else {
            b[k] = a[j];
            bh[k++] = (lastRun == 2) ? ah[j] : (lastRun == 0 ? 0 : mEmit);
            mEmit = m; lastRun = 2; ++j;
            if (j < r) {
                int hr = ah[j];
                if (hr > m)      cmp = 1;
                else if (hr < m) { m = hr; cmp = -1; }
                else { auto c = cmpFrom(a[i], a[j], m); m = c.first; cmp = c.second; }
            }
        }
    }
    while (i < mid) {
        b[k] = a[i];
        bh[k++] = (lastRun == 1) ? ah[i] : (lastRun == 0 ? 0 : mEmit);
        mEmit = m; lastRun = 1; ++i;
    }
    while (j < r) {
        b[k] = a[j];
        bh[k++] = (lastRun == 2) ? ah[j] : (lastRun == 0 ? 0 : mEmit);
        mEmit = m; lastRun = 2; ++j;
    }
}

inline void lcpMergeSortRec(vector<string> &a, vector<int> &ah,
                            vector<string> &b, vector<int> &bh, int l, int r) {
    if (r - l < 2) { if (r - l == 1) ah[l] = 0; return; }
    int mid = (l + r) / 2;
    lcpMergeSortRec(a, ah, b, bh, l, mid);
    lcpMergeSortRec(a, ah, b, bh, mid, r);
    lcpMergeRange(a, ah, l, mid, r, b, bh);
    for (int t = l; t < r; ++t) { a[t] = b[t]; ah[t] = bh[t]; }
}

inline void stringMergeSort(vector<string> &a) {
    if (a.size() < 2) return;
    int n = (int)a.size();
    vector<int> ah(n), bh(n);
    vector<string> b(n);
    lcpMergeSortRec(a, ah, b, bh, 0, n);
}

inline bool lessFrom(const string &a, const string &b, int d) {
    int i = d;
    int la = (int)a.size(), lb = (int)b.size();
    while (i < la && i < lb) {
        ++g_charCmp;
        if (a[i] != b[i]) return (unsigned char)a[i] < (unsigned char)b[i];
        ++i;
    }
    return la < lb;
}

inline void insertionSortFrom(vector<string> &a, int lo, int hi, int d) {
    for (int i = lo + 1; i <= hi; ++i)
        for (int j = i; j > lo && lessFrom(a[j], a[j - 1], d); --j)
            swap(a[j], a[j - 1]);
}

inline void msdRadixSortRec(vector<string> &a, vector<string> &aux,
                            int lo, int hi, int d) {
    static constexpr int R_CUTOFF = 16;
    if (hi - lo < R_CUTOFF) { insertionSortFrom(a, lo, hi, d); return; }
    const int R = 256;
    vector<int> count(R + 2, 0);
    vector<int> key(hi - lo + 1);
    for (int i = lo; i <= hi; ++i) {
        key[i - lo] = charAt(a[i], d);
        ++count[key[i - lo] + 2];
    }
    for (int r = 0; r < R + 1; ++r) count[r + 1] += count[r];
    for (int i = lo; i <= hi; ++i) aux[count[key[i - lo] + 1]++] = a[i];
    for (int i = lo; i <= hi; ++i) a[i] = aux[i - lo];
    for (int r = 0; r < R; ++r)
        msdRadixSortRec(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1);
}

inline void msdRadixSort(vector<string> &a) {
    if (a.size() < 2) return;
    vector<string> aux(a.size());
    msdRadixSortRec(a, aux, 0, (int)a.size() - 1, 0);
}

inline void msdRadixQuickSortRec(vector<string> &a, vector<string> &aux,
                                 int lo, int hi, int d) {
    static constexpr int ALPHABET = 74;
    if (hi - lo + 1 < ALPHABET) { stringQuickSortRec(a, lo, hi, d); return; }
    const int R = 256;
    vector<int> count(R + 2, 0);
    vector<int> key(hi - lo + 1);
    for (int i = lo; i <= hi; ++i) {
        key[i - lo] = charAt(a[i], d);
        ++count[key[i - lo] + 2];
    }
    for (int r = 0; r < R + 1; ++r) count[r + 1] += count[r];
    for (int i = lo; i <= hi; ++i) aux[count[key[i - lo] + 1]++] = a[i];
    for (int i = lo; i <= hi; ++i) a[i] = aux[i - lo];
    for (int r = 0; r < R; ++r)
        msdRadixQuickSortRec(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1);
}

inline void msdRadixQuickSort(vector<string> &a) {
    if (a.size() < 2) return;
    vector<string> aux(a.size());
    msdRadixQuickSortRec(a, aux, 0, (int)a.size() - 1, 0);
}
