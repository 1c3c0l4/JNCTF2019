# JNCTF-2019 : Basetoo

## **【原理】**

这是一道算法分析题，灵感来源于Base64，算法结构也跟base64非常相似，如果对base64的原理掌握比较清楚的话会很简单。

## **【目的】**

考察对二进制位操作的熟悉度。

## **【环境】**

C

## **【工具】**

电脑

## **【步骤】**

使用 IDA 32 直接打开可以看到

![1570838580543](assets\1570838580543.png)

逻辑很简单就是 v3 和 v13 保存的是个字符串 `QTSrSVdLXTacdZb5YUb5YNY1QMDQ` ，v12 保存的是密码本，跟base64是一样的。v6 保存的是输入，也就是flag，v10保存的是加密后字符串的长度，是 ceil(len(v6 /3)) * 4，从后面的循环中可看出，这个循环是把三个字符转化成四个字符。v15, v16是两个计数器，可以看做 i，j。分析循环逻辑可以看到：

把三个字符串共计24位数据进行如下方式切割组合：

![1570840410035](assets\1570840410035.png)

知道原理后就可以写出解密脚本了。

```c
#include <stdio.h>
#include <string.h>

int main() {
    unsigned char *code = "QTSrSVdLXTacdZb5YUb5YNY1QMDQ";
    int table[] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0   - 15
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 16  - 31
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, // 32  - 47
        52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1, // 48  - 63
        -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,           // 64  - 79
        15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // 80  - 95
        -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, // 96  - 111
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1, // 112 - 127
    };
    unsigned char flag[20];

    for (int i = 0, j = 0; i < 28; i += 4, j += 3) {
        flag[j] = ((((table[code[i]] & 0x30) | (table[code[i + 1]] & 0x0C) | (table[code[i + 2]] & 0x03)) << 2) & 0xFC) | ((table[code[i + 3]] >> 4) & 0x03);
        flag[j + 1] = ((((table[code[i + 2]] & 0x30) | (table[code[i]] & 0x0C) | (table[code[i + 1]] & 0x03)) << 2) & 0xFC) | ((table[code[i + 3]] >> 2) & 0x03);
        flag[j + 2] = ((((table[code[i + 1]] & 0x30) | (table[code[i + 2]] & 0x0C) | (table[code[i]] & 0x03)) << 2) & 0xFC) | (table[code[i + 3]] & 0x03);
    }

    printf("%s", flag);
    return 0;
}
```

`JNCTF{I_love_base!}`

## **【总结】**

软件逆向分析的难度主要在于对算法的理解上面，如果对算法的理解足够透彻的话，难度还是很低的。

顺便放出加密脚本

```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    unsigned char flag[100];
    unsigned char *code = malloc(sizeof(unsigned char) * 28);
    scanf("%s", flag);
    strcpy(code, "QTSrSVdLXTacdZb5YUb5YNY1QMDQ");

    unsigned char *table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned char *res;
    int str_len = strlen(flag);
    int len = 0;
    len = str_len % 3 == 0 ? str_len / 3 << 2 : (str_len / 3 + 1) << 2;
    if (len != 28) {
        printf("You are failed! Guy");
        system("color 04");
        return 0;
    }

    flag[19] = 0;
    flag[20] = 0;

    res = malloc(sizeof(unsigned char)*len);

    for (int i = 0, j = 0; i < len-2; j += 3,i += 4) {
        res[i] = table[((flag[j] & 0xC0) | (flag[j + 1] & 0x30) | (flag[j + 2] & 0x0C)) >> 2];
        res[i + 1] = table[((flag[j + 2] & 0xC0) | (flag[j] & 0x30) | (flag[j + 1] & 0x0C)) >> 2];
        res[i + 2] = table[((flag[j + 1] & 0xC0) | (flag[j + 2] & 0x30) | (flag[j] & 0x0C)) >> 2];
        res[i + 3] = table[((flag[j] << 4) & 0x30) | ((flag[j + 1] << 2) & 0x0C) | (flag[j + 2] & 0x03)];
    }

    for (int i = 0; i < len; i++) {
        if (res[i] != code[i]) {
            printf("You are failed! Guy!");
            system("color 04");
            return 0;
        }
    }


    printf("....Amazing!");
    system("color 02");
    return 0;
}
```

