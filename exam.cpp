#include <iostream>
#include <list>
#include <iomanip>
#include <iterator>
#include <cmath>
using namespace std;

bool readList(list<double> &a) {
    int n;
    if (!(cin >> n) || n < 1 || n > 500)
        return false;
    for (int i = 0; i < n; i++) {
        double x;
        if (!(cin >> x) || !isfinite(x))
            return false;
        a.push_back(x);
    }
    return true;
}

int main() {
    list<double> a, b;
    if (!readList(a) || !readList(b)) {
        cout << "Error: invalid input" << endl;
        return 1;
    }

    a.sort();
    b.sort();
    a.merge(b);
    a.unique();
    cout << fixed << setprecision(3);

    for (double x : a)
        cout << x << " ";
    cout << endl;

    int k = a.size();
    double median;
    if (k % 2 == 1)
        median = *next(a.begin(), k / 2);
    else
        median = (*next(a.begin(), k / 2 - 1) + *next(a.begin(), k / 2)) / 2;

    double range = a.back() - a.front();

    cout << "Median: " << median << endl;
    cout << "Range: " << range << endl;
    return 0;
}
