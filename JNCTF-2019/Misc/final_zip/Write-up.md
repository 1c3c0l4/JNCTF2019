# JNCTF-2019 : final_zip

## **【原理】**

爆破密码+伪加密+crc32碰撞

## **【目的】**

zip隐写综合能力考查

## **【环境】**

无

## **【工具】**

zip压缩包密码爆破工具

## **【步骤】**

1、看到提示，知道密码的结构，生成字典进行爆破

```python
import string

pw = "JNCTF"

s = string.digits + string.ascii_uppercase

f = open('dict.txt', 'w')
for a in s:
	for b in s:
		for c in s:
			for d in s:
				f.write(pw+a+b+c+d+'\n')
f.close()
```

生成字典

```
JNCTF0000
​```
JNCTFZZZN
JNCTFZZZO
JNCTFZZZP
JNCTFZZZQ
JNCTFZZZR
JNCTFZZZS
JNCTFZZZT
JNCTFZZZU
JNCTFZZZV
JNCTFZZZW
JNCTFZZZX
JNCTFZZZY
JNCTFZZZZ
```



最终还原密码：JNCTFK12D

2、看到提示，假作真时真亦假

利用winhex查看发现是伪加密

![2_1](C:/Users/Administrator/Desktop/江南大学2019信息安全技能大赛/compressed_package(压缩包)/2_1.png)

将加密位改为0，成功解压

3、压缩包中有10份flag，将flag分为10份

![3-1](C:/Users/Administrator/Desktop/江南大学2019信息安全技能大赛/compressed_package(压缩包)/3_1.png)

每一份的大小都是4，利用Crc32碰撞

```python
import zipfile
import binascii
import string

disc = string.printable
crcs = []
flag = ['*']*40


def getflag():
	for a in disc:
		for b in disc:
			for c in disc:
				for d in disc:
					txt = a+b+c+d
					crc = binascii.crc32(txt.encode('utf-8'))
					if crc in crcs:
						loc = crcs.index(crc)
						flag[loc*4:loc*4+4] = txt
						end_flag = ''.join(flag)
						print(end_flag)

def getcrc():
	zip_name = '还是压缩包' + '.zip'
	f = zipfile.ZipFile(zip_name, 'r')
	for i in range(10):
		flag_name = 'flag_' + chr(i+48) + '.txt'
		zipinfor = f.getinfo(flag_name)
		crcs.append(int(zipinfor.CRC))

if __name__ == '__main__':
	getcrc()
	# print((crcs))
	getflag()
```

获得最终结果：

```
************************************0!!}
************************d_zi********0!!}
********************eated_zi********0!!}
********ilip********eated_zi********0!!}
********ilip********eated_zip_in****0!!}
********ilip****z_created_zip_in****0!!}
****F{Philip****z_created_zip_in****0!!}
JNCTF{Philip****z_created_zip_in****0!!}
JNCTF{Philip****z_created_zip_in_2000!!}
JNCTF{Philip_Katz_created_zip_in_2000!!}
[Finished in 83.4s]
```

flag: JNCTF{Philip_Katz_created_zip_in_2000!!}

## **【总结】**

无