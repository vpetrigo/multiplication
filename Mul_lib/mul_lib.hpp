#ifndef MUL_LIB_HPP
#define MUL_LIB_HPP

#include <vector>
#include <iostream>

namespace Mul_lib {
    std::vector<int> naive_mul(const std::vector<int>& x, const std::vector<int>& y);
    std::vector<int> karatsuba_mul(const std::vector<int>& x, const std::vector<int>& y);
    std::vector<int> get_number(std::istream& is);
    void print_res(const std::vector<int>& v, std::ostream& os);
    void extend_vec(std::vector<int>& v, int len);
    void finalize(std::vector<int>& res);
} // Mul_lib
#endif // MUL_LIB_HPP