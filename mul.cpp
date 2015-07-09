#include <climits>
#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

constexpr int base = 1e2;
constexpr int len_f_naive = 16;
constexpr int dig_size = 10;
constexpr int add_zero = base / dig_size;

vector<int> get_number(istream& is);
vector<int> get_number_imp(istream& is);
void print_vec(const vector<int>& v);
void print_res(const vector<int>& v);
void print_res_imp(const vector<int>& v, ostream& os);
void extend_vec(vector<int>& v, int len);
vector<int> naive_mul(const vector<int>& x, const vector<int>& y);
vector<int> karatsuba_mul(const vector<int>& x, const vector<int>& y);
void finalize(vector<int>& res);
void print_vec_imp(const vector<int>& v);

int main() {
    vector<int> first, second;
    vector<int> res;
    ifstream ifs{"nums.txt"};
    ofstream ofs{"out.txt"};
    
    if (!ifs) {
        cerr << "Error: File could not be found\n";
        return 1;
    }
    
    first = get_number_imp(ifs);
    second = get_number_imp(ifs);
    
    int n = max(first.size(), second.size());
    
    extend_vec(first, n);
    extend_vec(second, n);
    
    
    clock_t t;
    t = clock();
    
    res = naive_mul(first, second);
    //res = karatsuba_mul(first, second);
    finalize(res);
    
    t = clock() - t;
    
    print_res_imp(res, ofs);
    
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

vector<int> get_number_imp(istream& is) {
    string snum;
    vector<int> vnum;
    unsigned int dig = 1;
    int n = 0;
    
    is >> snum;
    
    for (auto it = snum.crbegin(); it != snum.crend(); ++it) {
        n += (*it - '0') * dig;
        dig *= dig_size;
        
        if (dig == base) {
            vnum.push_back(n);
            n = 0;
            dig = 1;
        }
    }
    
    if (n != 0) {
        vnum.push_back(n);
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
    vector<int>::const_reverse_iterator cit = v.crbegin();

    while (!*cit) {
        ++cit;
    }
    
    while (cit != v.crend()) {
        cout << *cit++;
    }
    cout << endl;
}

void print_res_imp(const vector<int>& v, ostream& os) {
    auto it = v.crbegin();
    
    while (!*it) {
        ++it;
    }
    
    while (it != v.crend()) {
        int z = -1;
        int num = *it;
        
        if (num == 0) {
            num += 1;
        }
        
        if (num < add_zero) {
            z = 1;         
            
            while ((num *= dig_size) < add_zero) {
                ++z;
            }
        }
        
        if (z > 0) {
            while (z--) {
                os << '0';
            }
        }
        os << *it++;
    }
    
    os << endl;
}

void print_vec_imp(const vector<int>& v) {
    int pos = 0;
    for (int i : v) {
        cout << "v[" << pos++ << "]: " << i << endl;
    }
}
