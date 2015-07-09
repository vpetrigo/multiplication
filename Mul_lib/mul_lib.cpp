#include "mul_lib.hpp"

using namespace std;

namespace Mul_lib {
    constexpr int base = 1e2;
    constexpr int len_f_naive = 16;
    constexpr int dig_size = 10;
    constexpr int add_zero = base / dig_size;

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

    vector<int> get_number(istream& is) {
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

    void extend_vec(vector<int>& v, int len) {    
        while (len & (len - 1)) {
            ++len;
        }
        
        len -= v.size();
        
        while (len--) {
            v.push_back(0);
        }
    }

    void finalize(vector<int>& res) {
        for (int i = 0; i < res.size(); ++i) {
            res[i + 1] += res[i] / base;
            res[i] %= base;
        }
    }

    void print_res(const vector<int>& v, ostream& os) {
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

    void print_vec(const vector<int>& v) {
        int pos = 0;
        for (int i : v) {
            cout << "v[" << pos++ << "]: " << i << endl;
        }
    }
}