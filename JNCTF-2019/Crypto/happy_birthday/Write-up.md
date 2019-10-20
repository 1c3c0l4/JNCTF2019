# JNCTF-2019 : happy_birthday

## **【原理】**

社会主义核心价值观+md5爆破

## **【目的】**

认识社会主义核心价值观，爆破md5

## **【环境】**

无

## **【工具】**

无

## **【步骤】**

将密文进行社会主义核心价值观解密，得到残缺的md5：f9015c41\*fc7e0\*ac11*1b1d4\*a55799

发现残缺几位，但知道部分明文，写出对应的爆破脚本即可

```
import hashlib
e = 1
for a in range(0,128):
	for b in range(0,128):
		for c in range(0, 128):
			# JNCTF{C*lebrate_the_Bir*hday_of_*ur_Motherland}
			if e == 1:
				m = 'JNCTF{C' + chr(a) + 'lebrate_the_Bir' + chr(b) + 'hday_of_' + chr(c) + 'ur_Motherland}'
				flag = hashlib.md5()
				flag.update(m.encode('utf-8'))
				md5 = flag.hexdigest()
				print(m)
				# f9015c41*fc7e0*ac11*1b1d4*a55799
				if md5[0:8] == 'f9015c41':
					print(m + '-------------')
					print(md5)
					e = 0
			else:
				break
```



## **【总结】**

无