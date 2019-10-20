# JNCTF-2019 : randomness

## **【原理】**
`rand()` is *pseudo-random* numbers generator(PRNG).Usually,we use datetime as the arguments of `srand()` function to set the seed for `rand()` ,that will be hard to predict. However, if seed is determined , result of `rand()` is also determined, even if the program runs on different machine. By the way, default seed is `1`, if you use `rand()` before `srand()`. 

## **【目的】**
Known that the rand is not real random.

## **【环境】**
Ubuntu 18.04

## **【工具】**
Calculator .

## **【步骤】**
Write a simple program to show the random number in seed `0xdeadbeef`.

```c
#include <stdio.h>

int main(){
	srand(0xdeadbeef);
	for(int i=0;i<100;i+=1){
		printf("%d",rand());
		getchar();
	}
}
```

The use the right number to achive your goal.

```sh
352217057^972265918^0xdeadbeef
4087365808

lang@ubuntu  ~/JNCTF2019  nc localhost 34567
Can you get my Treasure?
4087365808
good job!
flagisme

```

## **【总结】**
use python or Linux C to predict the "random" number. 
