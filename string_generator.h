#pragma once
#include <bits/stdc++.h>
using namespace std;

class StringGenerator {
public:
    static constexpr int MIN_LEN = 10;
    static constexpr int MAX_LEN = 200;

    explicit StringGenerator(unsigned seed = 20260516u) : rng(seed) {
        for (char c = 'A'; c <= 'Z'; ++c) alphabet.push_back(c);
        for (char c = 'a'; c <= 'z'; ++c) alphabet.push_back(c);
        for (char c = '0'; c <= '9'; ++c) alphabet.push_back(c);
        for (char c : string("!@#%:;^&*()-.")) alphabet.push_back(c);
    }

    int alphabetSize() const { return (int)alphabet.size(); }

    string randomString(int len) {
        uniform_int_distribution<int> pick(0, (int)alphabet.size() - 1);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; ++i) s.push_back(alphabet[pick(rng)]);
        return s;
    }

    string randomString() {
        uniform_int_distribution<int> len(MIN_LEN, MAX_LEN);
        return randomString(len(rng));
    }

    vector<string> randomArray(int n) {
        vector<string> a;
        a.reserve(n);
        for (int i = 0; i < n; ++i) a.push_back(randomString());
        return a;
    }

    vector<string> reverseSortedArray(int n) {
        vector<string> a = randomArray(n);
        sort(a.begin(), a.end(), greater<string>());
        return a;
    }

    vector<string> almostSortedArray(int n, int swaps) {
        vector<string> a = randomArray(n);
        sort(a.begin(), a.end());
        if (n > 1) {
            uniform_int_distribution<int> pos(0, n - 1);
            for (int k = 0; k < swaps; ++k) {
                int i = pos(rng), j = pos(rng);
                swap(a[i], a[j]);
            }
        }
        return a;
    }

    vector<string> prefixedArray(int n) {
        int groups = max(1, (int)round(sqrt((double)n)));
        vector<string> prefixes;
        uniform_int_distribution<int> plen(20, 60);
        for (int g = 0; g < groups; ++g) prefixes.push_back(randomString(plen(rng)));
        uniform_int_distribution<int> pickGroup(0, groups - 1);
        uniform_int_distribution<int> slen(MIN_LEN, MAX_LEN);
        vector<string> a;
        a.reserve(n);
        for (int i = 0; i < n; ++i) {
            const string &p = prefixes[pickGroup(rng)];
            int total = max((int)p.size() + MIN_LEN, slen(rng));
            string s = p + randomString(total - (int)p.size());
            a.push_back(move(s));
        }
        return a;
    }

private:
    mt19937 rng;
    string alphabet;
};
