# JNCTF-2019 : easy_ttl

## **【原理】**

https://yq.aliyun.com/articles/571954

## **【目的】**

TTL隐写术

## **【环境】**

无

## **【工具】**

python、stegsolve

## **【步骤】**

了解一下TTL隐藏信息的方式，先把无效信息删除，接下来写脚本提取信息

```
s=''
with open('TTL.txt','r',encoding='utf-8') as f:
    line=f.readline().replace('\n','')
    while line:
        if line=='63':
            s=s+'00'
        elif line=='127':
            s=s+'01'
        elif line=='191':
            s=s+'10'
        else:
            s=s+'11'
        line=f.readline().replace('\n','')
for i in range(0,len(s),4):
    print(str(hex((int(s[i]+s[i+1]+s[i+2]+s[i+3],2))))[2:],end='')
```

根据文件头发现是明显的png文件，利用winhex十六进制编辑器生成图片，发现是一张二维码但无法扫描，经stegsolve进行黑白反色后可以扫描得到flag

JNCTF{TTl_1s_very_useFUl}

## **【总结】**

比较少见的隐写术，考察选手的信息收集能力和脚本解题能力。