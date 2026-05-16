#include <bits/stdc++.h>
using namespace std;

int lcpCompare(const string &a, const string &b) {
    size_t i = 0;
    while (i < a.size() && i < b.size() && a[i] == b[i]) i++;
    if (i == a.size() && i == b.size()) return 0;
    if (i == a.size()) return -1;
    if (i == b.size()) return 1;
    return (unsigned char)a[i] < (unsigned char)b[i] ? -1 : 1;
}

void merge(vector<string> &a, vector<string> &buf, int l, int m, int r) {
    int i = l, j = m, k = l;
    while (i < m && j < r) {
        if (lcpCompare(a[i], a[j]) <= 0) buf[k++] = a[i++];
        else buf[k++] = a[j++];
    }
    while (i < m) buf[k++] = a[i++];
    while (j < r) buf[k++] = a[j++];
    for (int t = l; t < r; t++) a[t] = buf[t];
}

void mergeSort(vector<string> &a, vector<string> &buf, int l, int r) {
    if (r - l < 2) return;
    int m = (l + r) / 2;
    mergeSort(a, buf, l, m);
    mergeSort(a, buf, m, r);
    merge(a, buf, l, m, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if (!(cin >> n)) return 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        getline(cin, a[i]);
        while (!a[i].empty() && a[i].back() == '\r') a[i].pop_back();
    }
    vector<string> buf(n);
    mergeSort(a, buf, 0, n);
    for (int i = 0; i < n; i++) cout << a[i] << "\n";
    return 0;
}
