#include "mul_lib.hpp"

using namespace std;

namespace Mul_lib {
    // current base functions use for operate with long integers
    constexpr int base = 1e7;
    // lenght of the long number for which naive multiplication
    // will be called in the Karatsuba function
    constexpr unsigned int len_f_naive = 32;
    // One digit size for numbers with bases multiple of ten
    constexpr int dig_size = 10;
    // How much zeroes have to be in the number
    constexpr int add_zero = base / dig_size;

    vector<long long> naive_mul(const vector<long long>& x, const vector<long long>& y) {
        auto len = x.size();
        vector<long long> res(2 * len);
        
        for (auto i = 0; i < len; ++i) {
            for (auto j = 0; j < len; ++j) {
                res[i + j] += x[i] * y[j];
            }
        }
        
        return res;
    }

    vector<long long> karatsuba_mul(const vector<long long>& x, const vector<long long>& y) {
        auto len = x.size();    
        vector<long long> res(2 * len);
        
        if (len <= len_f_naive) {
            return naive_mul(x, y);
        }
        
        auto k = len / 2;
        
        vector<long long> Xr {x.begin(), x.begin() + k};
        vector<long long> Xl {x.begin() + k, x.end()};
        vector<long long> Yr {y.begin(), y.begin() + k};
        vector<long long> Yl {y.begin() + k, y.end()};
        
        vector<long long> P1 = karatsuba_mul(Xl, Yl);
        vector<long long> P2 = karatsuba_mul(Xr, Yr);    
            
        vector<long long> Xlr(k);
        vector<long long> Ylr(k);
        
        for (auto i = 0; i < k; ++i) {
            Xlr[i] = Xl[i] + Xr[i];
            Ylr[i] = Yl[i] + Yr[i];
        }
        
        vector<long long> P3 = karatsuba_mul(Xlr, Ylr);
        
        for (auto i = 0; i < len; ++i) {
            P3[i] -= P2[i] + P1[i];
        }
        
        for (auto i = 0; i < len; ++i) {
            res[i] = P2[i];
        }

        for (auto i = len; i < 2 * len; ++i) {
            res[i] = P1[i - len];
        }

        for (auto i = k; i < len + k; ++i) {
            res[i] += P3[i - k];
        }
        
        return res;
    }

    vector<long long> get_number(istream& is) {
        string snum;
        vector<long long> vnum;
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

    void extend_vec(vector<long long>& v, size_t len) {    
        while (len & (len - 1)) {
            ++len;
        }
        
        v.resize(len);
    }

    void finalize(vector<long long>& res) {
        for (auto i = 0; i < res.size(); ++i) {
            res[i + 1] += res[i] / base;
            res[i] %= base;
        }
    }

    void print_res(const vector<long long>& v, ostream& os) {
        auto it = v.crbegin();
        
        // Passing leading zeroes
        while (!*it) {
            ++it;
        }
        
        while (it != v.crend()) {
            int z = -1;
            auto num = *it;
            
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

    void print_vec(const vector<long long>& v) {
        size_t pos = 0;
        for (auto& i : v) {
            cout << "v[" << pos++ << "]: " << i << endl;
        }
    }
}
