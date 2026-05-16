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
    quickSort(a, 0, n - 1, 0);
    for (int i = 0; i < n; i++) cout << a[i] << "\n";
    return 0;
}
