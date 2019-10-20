# JNCTF-2019：Matrix

## **【原理】**

利用 ASCII 码的特点实现的一种新的加密方法。

## **【目的】**

考察队字符串表示的理解，同时要熟练使用 Python 以及 Numpy 工具进行解题脚本的编写。

## **【环境】**

Python ： Numpy

## **【工具】**

Python ： Numpy

## **【步骤】**

解法有两种，一种是手算逆矩阵然后相乘得到结果（这里就不演示了，考研线性代数基础啊）

另外一种就是编程解了

```python
import numpy as np

key = 'SoEasy!'
k_m = np.array([list(bin(ord(i))[2:].rjust(7, '0')) for i in key], int)

res =  [[1, 1, 1, 0, 0, 1, 2],
        [4, 4, 2, 1, 1, 3, 5],
        [2, 2, 1, 1, 1, 2, 3],
        [5, 3, 2, 2, 2, 2, 5],
        [3, 3, 1, 1, 1, 2, 4],
        [5, 4, 3, 2, 1, 3, 5],
        [4, 4, 3, 2, 1, 3, 5]]

res = np.array(res, int)

flag_m = np.array(res @ np.linalg.inv(k_m), int).astype(str)
flag = ''.join([chr(int(eval('0b'+''.join(i)))) for i in flag_m])

print(flag)
```

## **【总结】**

细心的同学可能会发现，这个加密方式所依赖的是矩阵相乘以及矩阵的逆运算，所以就需要矩阵是可逆的，也就是说，不能出现两个相同的字符。所以，，有待改进！