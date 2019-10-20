# JNCTF-2019 : easy_wifi

## **【原理】**

抓取wifi握手包破解wifi密码

## **【目的】**

wifi密码破解

## **【环境】**

无

## **【工具】**

aircrack-ng

## **【步骤】**

准备一份弱密码字典直接攻击

aircrack-ng -w dic.txt ./easy_wifi.cap

得到密码为123456789

所以flag为JNCTF{123456789}

## **【总结】**

wifi弱密码非常容易被攻击（认真