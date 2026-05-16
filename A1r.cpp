#include <bits/stdc++.h>
using namespace std;

int charAt(const string &s, int d) {
    return d < (int)s.size() ? (unsigned char)s[d] : -1;
}

bool lessFrom(const string &a, const string &b, int d) {
    int i = d;
    while (i < (int)a.size() && i < (int)b.size()) {
        if (a[i] != b[i]) return (unsigned char)a[i] < (unsigned char)b[i];
        i++;
    }
    return a.size() < b.size();
}

void insertionSort(vector<string> &a, int lo, int hi, int d) {
    for (int i = lo + 1; i <= hi; i++)
        for (int j = i; j > lo && lessFrom(a[j], a[j - 1], d); j--)
            swap(a[j], a[j - 1]);
}

void msd(vector<string> &a, vector<string> &aux, int lo, int hi, int d) {
    if (hi - lo < 16) {
        insertionSort(a, lo, hi, d);
        return;
    }
    const int R = 256;
    vector<int> count(R + 2, 0);
    for (int i = lo; i <= hi; i++) count[charAt(a[i], d) + 2]++;
    for (int r = 0; r < R + 1; r++) count[r + 1] += count[r];
    for (int i = lo; i <= hi; i++) aux[count[charAt(a[i], d) + 1]++] = a[i];
    for (int i = lo; i <= hi; i++) a[i] = aux[i - lo];
    for (int r = 0; r < R; r++) msd(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1);
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
    vector<string> aux(n);
    if (n > 1) msd(a, aux, 0, n - 1, 0);
    for (int i = 0; i < n; i++) cout << a[i] << "\n";
    return 0;
}
