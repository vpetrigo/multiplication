#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

using namespace std;

constexpr int base = 10;

vector<int> get_number(istream& is);
void print_vec(const vector<int>& v);
void extend_vec(vector<int>& v, int len);
vector<int> naive_mul(const vector<int>& x, const vector<int>& y);
void finalize(vector<int>& res);

int main() {
    vector<int> first, second;
    vector<int> res;
    ifstream ifs{R"(C:/Users/Vladimir/Desktop/file.txt)"};
    
    first = get_number(ifs);
    second = get_number(ifs);
    
    int n = max(first.size(), second.size());
    
    if (second.size() < n) {
        extend_vec(second, n - second.size());
    }
    else {
        extend_vec(first, n - first.size());
    }
    
    clock_t t;
    t = clock();
    
    res = naive_mul(first, second);
    finalize(res);
    
    t = clock() - t;
    
    print_vec(res);
    
    cout << "It took me " << t << " cycles (" << t / CLOCKS_PER_SEC <<
        " seconds)\n";
    
    return 0;
}

vector<int> get_number(istream& is) {
    string snum;
    vector<int> vnum;
    is >> snum;
    
    for (auto it = snum.rbegin(); it != snum.rend(); ++it) {
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
