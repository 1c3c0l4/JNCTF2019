# JNCTF-2019 : i_love_china

## **【原理】**

socket编程

## **【目的】**

考察选手网络编程能力

## **【环境】**

python

## **【工具】**

python

## **【步骤】**

简单判断后写出脚本即可

附解题脚本

```
#!/usr/bin/python3
# 文件名：client.py

# 导入 socket、sys 模块
import socket
import sys

# 创建 socket 对象
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) 

# 设置ip
host =

# 设置端口
port = 
addr = (host,port)
# 连接服务，指定主机和端口
s.connect((host, port))
dic=['prosperity','democracy','civility','harmony','freedom','equality','justice','rule_of_law','patriotism','dedication','integrity','friendship']
i=0
# 接收并发送数据
while True:
    msg = s.recv(1024)
    print(msg.decode('utf-8'),end='')
    if i<len(dic):
        s.send(dic[i].encode())
        i=i+1
```

## **【总结】**

题目限定了要在10s中打出社会主义核心价值观的英语，别想手打了兄弟，socket编程搞一搞吧

