#include <bits/stdc++.h>
using namespace std;

int charAt(const string &s, int d) {
    return d < (int)s.size() ? (unsigned char)s[d] : -1;
}

void quickSort(vector<string> &a, int lo, int hi, int d) {
    if (hi <= lo) return;
    swap(a[lo], a[lo + (hi - lo) / 2]);
    int lt = lo, gt = hi, i = lo + 1;
    int v = charAt(a[lo], d);
    while (i <= gt) {
        int t = charAt(a[i], d);
        if (t < v) swap(a[lt++], a[i++]);
        else if (t > v) swap(a[i], a[gt--]);
        else i++;
    }
    quickSort(a, lo, lt - 1, d);
    if (v >= 0) quickSort(a, lt, gt, d + 1);
    quickSort(a, gt + 1, hi, d);
}

void msd(vector<string> &a, vector<string> &aux, int lo, int hi, int d) {
    if (hi - lo + 1 < 74) {
        quickSort(a, lo, hi, d);
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
    if (n > 0) msd(a, aux, 0, n - 1, 0);
    for (int i = 0; i < n; i++) cout << a[i] << "\n";
    return 0;
}
