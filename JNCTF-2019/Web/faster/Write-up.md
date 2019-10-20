

# JNCTF-2019 : faster

## **【原理】**

网页快速刷新，考察编程解题能力

## **【目的】**

考察选手的网络编程能力，基本用手是来不及的

## **【环境】**

Apache+php

## **【工具】**

不限制语言，推荐python（requests+re正则即可）

## **【步骤】**

抓包观察一下发送至check.php进行检验，写脚本即可

```
#附解题脚本
import requests
import re
url = "http://172.18.146.241:31006/index.php"
html = requests.get(url)
html.encoding='utf-8'
res = re.findall(r'<textarea.*?>(.*?)</textarea>', html.text)
line=" ".join(res)
list=line[:-1].replace('×',' ').split()
array0=[]
array1=[]
summ=[]
for i in list[0]:
    array0.append(int(i))
for i in list[1]:
    array1.append(int(i))
if len(array0)>=len(array1):
    sum0=int(list[0])
    array1.reverse()
    for i in range(len(array1)):
        zero='0'*i
        num0=sum0*array1[i]
        num0=str(num0)+zero
        summ.append(int(num0))
else:
    sum1 = int(list[1])
    array0.reverse()
    for i in range(len(array0)):
        zero = '0' * i
        num0 = sum1 * array0[i]
        num0 = str(num0) + zero
        summ.append(int(num0))
answer=str(sum(summ))
ans = {
    "answer":answer
}
url2 = 'http://172.18.146.241:31006/work.php'
s = requests.post(url=url2,data=ans,cookies=html.cookies)
b=str(s.content, encoding="utf-8")
a = re.findall('JNCTF{.*}', b,re.I)
print(a)
```



## **【总结】**

理论上所有浏览器能做的事情，都可以通过编程来交互来实现，这里也只是编程将提交答案的过程自动化了，所以其实抢课的过程也可以（我没说