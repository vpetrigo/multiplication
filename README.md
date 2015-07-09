# Multiplication for big integers

Here is very basic implementation of naive multiplication (which takes ![BigO^2](https://upload.wikimedia.org/math/d/d/d/ddd68bd29c2494cbe63f203a70e544e3.png))
and Karatsuba algorithm (which takes ![BigO^log](https://upload.wikimedia.org/math/a/f/0/af0bdd77b22562e62e5ba2233558d7bd.png)).

1. Standard sequence for both algorithms:
    ```C++
    // Getting number from the input (stdin, file, etc.)
    vector<int> first = get_number(cin);
    vector<int> second = get_number(cin);

    // Select the biggest length of two numbers
    int n = max(first.size(), second.size());

    // Extend two vectors to the nearest square of 2
    extend_vec(first, n);
    extend_vec(second, n);   
    ```
2. Then you should select prefered multiplication algorithm.
    - For using naive multiplication:
    ```C++
    vector<int> res = naive_mul(first, second);
    ```
    - For using Karatsuba multiplication:
    ```C++
    vector<int> res = karatsuba_mul(first, second);
    ```
3. And finalize your result by using`finalize(res);`
4. Call `print_res()` function for getting the result
    ```C++
    // Pass the result vector to it
    print_res(res);
    ```
5. Enjoy the vast output. 

Now, it is using vectors for storing numbers with base 10. Further improvments should be
to change base of all numbers which are stored in input vectors.
