#include <stdio.h>
int treasure=0;
void stdaffair(){
    setbuf(stdin,0);
    setbuf(stdout,0);
    setbuf(stderr,0);
}

void award(){
    system("cat ./flag");
}

void magic(){
    srand(0xdeadbeef);
}

void lock(){
    int p=rand();
    for(int i=0;i<10;i++){
    	treasure=p^rand();
    }
}
int main(){
    int key=0;
    stdaffair();
    magic();
    lock();
    puts("Can you get my Treasure?");
    scanf("%d",&key);
    if ((key^treasure)==0xdeadbeef){
	    puts("good job!");
	    award();
    }else{
	    puts("Maybe you can try 2^32 times!");
    }
    return 0;
}
