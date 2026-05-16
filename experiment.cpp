#include <bits/stdc++.h>
#include "string_sort_tester.h"
using namespace std;

unsigned long long g_charCmp = 0;

int main(int argc, char **argv) {
    string csvPath = argc > 1 ? argv[1] : "results.csv";
    StringSortTester tester;
    try {
        tester.runFullStudy(csvPath);
    } catch (const exception &e) {
        cerr << "Ошибка: " << e.what() << '\n';
        return 1;
    }
    cerr << "Готово. Результаты записаны в " << csvPath << '\n';
    return 0;
}
