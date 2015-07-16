/*!
\file
\brief Header file with all functions which may help to do multiplication

Here are definitions of the function for getting long integer numbers from
standard input or file streams or whatever streams it needs, the function for
doing multiplication (implemented naive and Karatsuba algorithms) and some other
functions for helping in result representation.
*/
#ifndef MUL_LIB_HPP
#define MUL_LIB_HPP

#include <vector>
#include <iostream>

namespace Mul_lib {
    /*!    
    Naive multiplication algorithm. Does multiplication like we all got used to:
    12 * 23 =   12
              x 23
              ----
                36
               24
              ----
               276
    It has O(n^2) complexity
    \param  x,y Two long integers
    \return Product of multiplication
    */
    std::vector<long long> naive_mul(const std::vector<long long>& x, const std::vector<long long>& y);
    /*!    
    Karatsuba multiplication algorithm. Uses idea of divide and conquer algorithm.
    More information about it you could find here https://en.wikipedia.org/wiki/Karatsuba_algorithm
    It has ~O(n^1.59) complexity
    \param  x,y Two long integers
    \return Product of multiplication
    */    
    std::vector<long long> karatsuba_mul(const std::vector<long long>& x, const std::vector<long long>& y);
    /*!
    Get a long integer from input stream
    \param is some input stream which will be used for number getting
    \return long integer
    */
    std::vector<long long> get_number(std::istream& is);
    /*!
    Output the result to a selected output stream
    \param [in] v long integer
    \param [out] os output stream the long integer will be output to.
    \return long integer in the little endian format according to internal base value
    */
    void print_res(const std::vector<long long>& v, std::ostream& os);
    /*!
    Output the result to a selected output stream
    \param [out] v long integer which will be extented to size of the closest power of two
    \param [in] len length according to it will be extended
    */
    void extend_vec(std::vector<long long>& v, size_t len);
    /*!
    Finalize the result of multiplication.
    For example we have a long number with base 100:
        | 0  |1| 2 |3|
    v = {1000,8,123,0}
    finalize() function goes through the vector and calculate carry:
    v[1] += v[0] / 100
    v[0] %= 100
        |0| 1|2 |3|
    v = {0,10,23,1}
    
    \param [out] v long integer which will be extented to size of the closest power of two
    \param [in] len length according to it will be extended
    */
    void finalize(std::vector<long long>& res);
    void print_vec(const std::vector<long long>& v);
} // Mul_lib
#endif // MUL_LIB_HPP