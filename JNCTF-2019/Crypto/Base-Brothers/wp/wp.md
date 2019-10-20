# JNCTF-2019 : Base 家族
  ## **【原理】**

**加密脚本**

```python
from base64 import b64encode, b16encode

flag = b'JNCTF{esxcfruhnmki}'

# 加密
en_flag = b16encode(b64encode(flag))
```

  ## **【目的】**
考察对基础编程语言以及搜索引擎的了解，同时锻炼对密码的敏感度。

  ## **【环境】**

python

  ## **【工具】**
- Python 环境 或者 浏览器

## **【步骤】**

**解密脚本**

```python
from base64 import b64encode, b16encode, b64decode, b16decode

en_flag = b'536B354456455A374D56396B4D4639754D446466597A5A795A563833627A4239'

# 解密
result = b64decode(b16decode(en_flag))
```



  ## **【总结】**

**Flag**

```raw
JNCTF{1_d0_n07_c6re_7o0}
```

