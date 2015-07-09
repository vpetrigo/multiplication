#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

constexpr int base = 10;
constexpr int len_f_naive = 16;

vector<int> get_number(istream& is);
void print_vec(const vector<int>& v);
void print_res(const vector<int>& v);
void extend_vec(vector<int>& v, int len);
vector<int> naive_mul(const vector<int>& x, const vector<int>& y);
vector<int> karatsuba_mul(const vector<int>& x, const vector<int>& y);
void finalize(vector<int>& res);

int main() {
    vector<int> first, second;
    vector<int> res;
    ifstream ifs{"nums.txt"};
    
    if (!ifs) {
        cerr << "Error: File could not be found\n";
        return 1;
    }
    
    first = get_number(cin);
    second = get_number(cin);
    
    int n = max(first.size(), second.size());
    
    extend_vec(first, n);
    extend_vec(second, n);
    
    
    clock_t t;
    t = clock();
    
    //res = naive_mul(first, second);
    res = karatsuba_mul(first, second);
    finalize(res);
    
    t = clock() - t;
    
    print_res(res);
    
    cout << "It took me " << t << " cycles (" << t / CLOCKS_PER_SEC <<
        " seconds)\n";
    
    return 0;
}

vector<int> get_number(istream& is) {
    string snum;
    vector<int> vnum;
    is >> snum;
    
    for (auto it = snum.crbegin(); it != snum.crend(); ++it) {
        vnum.push_back(*it - '0');
    }
    
    return vnum;
}

void print_vec(const vector<int>& v) {
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        cout << *it;
    }
    cout << endl;
}

void extend_vec(vector<int>& v, int len) {    
    while (len & (len - 1)) {
        ++len;
    }
    
    len -= v.size();
    
    while (len--) {
        v.push_back(0);
    }
}

vector<int> naive_mul(const vector<int>& x, const vector<int>& y) {
    int len = x.size();
    vector<int> res(2 * len);
    
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len; ++j) {
            res[i + j] += x[i] * y[j];
        }
    }
    
    return res;
}

void finalize(vector<int>& res) {
    for (int i = 0; i < res.size(); ++i) {
        res[i + 1] += res[i] / base;
        res[i] %= base;
    }
}

vector<int> karatsuba_mul(const vector<int>& x, const vector<int>& y) {
    int len = x.size();    
    vector<int> res(2 * len);
    
    if (len <= len_f_naive) {
        return naive_mul(x, y);
    }
    
    int k = len / 2;
    
    vector<int> Xr {x.begin(), x.begin() + k};
    vector<int> Xl {x.begin() + k, x.end()};
    vector<int> Yr {y.begin(), y.begin() + k};
    vector<int> Yl {y.begin() + k, y.end()};
    
    vector<int> P1 = karatsuba_mul(Xl, Yl);
    vector<int> P2 = karatsuba_mul(Xr, Yr);    
        
    vector<int> Xlr(k);
    vector<int> Ylr(k);
    
    for (int i = 0; i < k; ++i) {
        Xlr[i] = Xl[i] + Xr[i];
        Ylr[i] = Yl[i] + Yr[i];
    }
    
    vector<int> P3 = karatsuba_mul(Xlr, Ylr);

    for (int i = 0; i < len; ++i) {
        P3[i] -= P2[i] + P1[i];
    }

    for (int i = 0; i < len; ++i) {
        res[i] = P2[i];
    }

    for (int i = len; i < 2 * len; ++i) {
        res[i] = P1[i - len];
    }

    for (int i = k; i < len + k; ++i) {
        res[i] += P3[i - k];
    }
    
    return res;
}

void print_res(const vector<int>& v) {
    int pos = v.size() - 1;

    while (!v[pos]) {
        --pos;
    }
    
    while (pos >= 0) {
        cout << v[pos--];
    }
    cout << endl;
}
