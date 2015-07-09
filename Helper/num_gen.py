#!/usr/bin/env python3

from random import randint

nums = [randint(10 ** 50000, 10 ** 50001) for _ in range(2)]

with open(r'../nums.txt', 'w') as f:
    for i in nums:
        print(i, file=f)
