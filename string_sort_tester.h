#pragma once
#include <bits/stdc++.h>
#include "string_generator.h"
#include "sorts.h"
using namespace std;

class StringSortTester {
public:
    struct Algorithm {
        string name;
        string kind;
        function<void(vector<string> &)> sort;
    };

    struct Measurement {
        string arrayType;
        int size;
        string algorithm;
        string kind;
        double timeMs;
        unsigned long long charOps;
    };

    StringSortTester() {
        algorithms = {
            {"StandardQuickSort", "standard",    standardQuickSort},
            {"StandardMergeSort", "standard",    standardMergeSort},
            {"StringQuickSort",   "specialized", stringQuickSort},
            {"StringMergeSort",   "specialized", stringMergeSort},
            {"MsdRadixSort",      "specialized", msdRadixSort},
            {"MsdRadixQuickSort", "specialized", msdRadixQuickSort},
        };
    }

    Measurement measure(const Algorithm &algo, const string &arrayType,
                         const vector<string> &input) {
        vector<string> reference = input;
        sort(reference.begin(), reference.end());

        vector<string> data = input;
        g_charCmp = 0;
        algo.sort(data);
        unsigned long long ops = g_charCmp;
        if (data != reference)
            throw runtime_error("Некорректная сортировка: " + algo.name +
                                 " на массиве типа " + arrayType);

        const double minTotalMs = 50.0;
        const int minRuns = 5, maxRuns = 100000;
        double totalMs = 0.0;
        int runs = 0;
        while (runs < maxRuns && (runs < minRuns || totalMs < minTotalMs)) {
            data = input;
            auto t0 = chrono::steady_clock::now();
            algo.sort(data);
            auto t1 = chrono::steady_clock::now();
            totalMs += chrono::duration<double, milli>(t1 - t0).count();
            ++runs;
        }
        return {arrayType, (int)input.size(), algo.name, algo.kind,
                totalMs / runs, ops};
    }

    void runFullStudy(const string &csvPath, int maxSize = 3000, int step = 100) {
        StringGenerator gen;

        vector<pair<string, vector<string>>> masters = {
            {"random",   gen.randomArray(maxSize)},
            {"reverse",  gen.reverseSortedArray(maxSize)},
            {"almost",   gen.almostSortedArray(maxSize, maxSize / 100)},
            {"prefixed", gen.prefixedArray(maxSize)},
        };

        ofstream out(csvPath);
        out << "array_type,size,algorithm,kind,time_ms,char_ops\n";

        for (auto &m : masters) {
            for (int n = step; n <= maxSize; n += step) {
                vector<string> sub(m.second.begin(), m.second.begin() + n);
                for (auto &algo : algorithms) {
                    Measurement r = measure(algo, m.first, sub);
                    out << r.arrayType << ',' << r.size << ',' << r.algorithm
                        << ',' << r.kind << ',' << fixed << setprecision(6)
                        << r.timeMs << ',' << r.charOps << '\n';
                }
            }
            cerr << "Завершён тип массива: " << m.first << '\n';
        }
        out.close();
    }

private:
    vector<Algorithm> algorithms;
};
