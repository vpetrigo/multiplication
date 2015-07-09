#!/usr/bin/env python3

import unittest

class TestMultiplication(unittest.TestCase):
    def test_mul(self):
        inp = open(r'../nums.txt')
        
        num1 = int(inp.readline())
        num2 = int(inp.readline())
        res = num1 * num2
        
        cpp_out = open(r'../out.txt')
        res_cpp = int(cpp_out.readline())
        
        inp.close()
        cpp_out.close()
        
        self.assertEqual(res, res_cpp)
        
        
if __name__ == '__main__':
    unittest.main()
    input()