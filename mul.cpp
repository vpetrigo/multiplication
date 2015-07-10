#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "mul_lib.hpp"

using namespace std;
using namespace Mul_lib;

int main() {
    vector<int> first, second;
    vector<int> res;
    ifstream ifs{"nums.txt"};
    ofstream ofs{"out.txt"};
    
    if (!ifs) {
        cerr << "Error: File could not be found\n";
        return 1;
    }
    
    first = get_number(ifs);
    second = get_number(ifs);
    
    int n = max(first.size(), second.size());
    
    extend_vec(first, n);
    extend_vec(second, n);
    
    
    clock_t t;
    t = clock();
    
    res = naive_mul(first, second);
    finalize(res);
    
    t = clock() - t;
    
    print_res(res, ofs);
    
    cout << "Naive algorithm took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC <<
        " seconds)\n";
    
    t = clock();
    res = karatsuba_mul(first, second);
    finalize(res);
    
    t = clock() - t;
    
    
    print_res(res, ofs);
    
    cout << "Karatsuba algorithm took me " << t << " cycles (" << static_cast<float> (t) / CLOCKS_PER_SEC <<
        " seconds)\n";
    
    return 0;
}

