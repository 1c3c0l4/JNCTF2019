# JNCTF-2019：**贺词**

## **【原理】**

一次性密码本使用XOR重复使用所带来的的爆破漏洞；

**加密脚本**

```python
from base64 import b64encode

flag = 'ertyuioio'

msgs = ['The estab', 'lishment ', 'of new Ch', 'ina is di', 'fficult. ', 'We should', ' remember', 
        ' history ', 'and be gr', 'ateful to', ' everyone', ' who has ', 'given out', ' youth an',
        'd life. N', 'ow we sho', 'uld study', ' hard, en', 'rich ours', 'elves, be', ' a useful',
        ' person, ', 'and contr', 'ibute our', ' own stre', 'ngth to t', 'he develo', 'pment of ',
        'the mothe', 'rland.   ']

num = len(msgs)

c = [''] * num

for i in range(9):
    for j in range(num):
        c[j] += chr(ord(flag[i]) ^ ord(msgs[j][i]))

for i in range(num):
    msgs[i] = b64encode(c[i].encode('utf-8')).decode('utf-8')

print(msgs)
```

## **【目的】**

考察大家对简单的密码学的了解以及使用脚本解题的能力。

## **【环境】**

Python

## **【工具】**

Python

## **【步骤】**

加密和一次性可以想到，一次性密码本，而这里是使用的同一个字符串，故肯定对原字符串进行了分组处理，所以我们可以使用想到，这应该是一次性密码本多次使用带来的漏洞，而题目中又给了提示，说明被加密字符串仅含有英文字母，和常见标点符号。而一次性密码本的加密多是使用的 XOR，这样处理后的字符多数是不可见的，所以需要 base 一下。

**解密脚本**

```python
from base64 import b64encode, b64decode

msgs = ['MRoRWRAaGwgN', 'CRsHERgMAR1P', 'ChRUFxAeTyoH', 'DBwVWRwaTw0G', 'AxQdGgAFG0dP', 'MhdUCh0GGgUL', 'RQARFBAEDQwd', 'RRodCgEGHRBP', 'BBwQWRcMTw4d', 'BAYRHwAFTx0A', 'RRcCHAcQAAcK', 'RQUcFlUBDhpP', 'AhsCHBtJABwb', 'RQsbDAEBTwgB', 'AVIYEBMMQUkh', 'CgVUDhBJHAEA', 'EB4QWQYdGg0W', 'RRoVCxFFTwwB', 'FxsXEVUGGhsc', 'AB4CHAZFTwsK', 'RRNUDAYMCRwD', 'RQIRCwYGAUVP', 'BBwQWRYGAR0d', 'DBABDRBJABwd', 'RR0DF1UaGxsK', 'CxUAEVUdAEkb', 'DRdUHRAfCgUA', 'FR8RFwFJAA9P', 'ERoRWRgGGwEK', 'Fx4VFxFHT0lP']

num = len(msgs) # here

# 解密
c = []
for i in msgs:
    c.append(b64decode(i))
    
def find(buf, my_msg, n):
    if n >= 9:
        print('JNCTF{', buf, '}', sep='') # here
        print(''.join(my_msg))
        return
    for j in range(97, 123):
        for k in range(num):
            if c[k][n] ^ j not in range(97, 123) and c[k][n] ^ j not in range(65, 91) and c[k][n] ^ j not in [32, 46, 44]:
                break
        if k >= num-1:
            temp = my_msg.copy()
            for i in range(num):
                temp[i] += chr(c[i][n] ^ j)
            find(buf+chr(j), temp, n+1)

flag = ''
msg =  [''] * num
find(flag, msg, 0)

```

## **【总结】**

这题的难点在于如何把自己的思路使用脚本编写出来，题目的思路很好理解，但是在解题的过程中需要很多的编程方面的知识，熟练使用编程工具还是很必要的。