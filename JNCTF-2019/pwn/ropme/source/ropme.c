#include <stdio.h>

void daily(){
  setvbuf(stdout, 0, 2, 0);
  setvbuf(stdin, 0, 1, 0);
  setvbuf(stderr, 0, 1, 0);
  alarm(20);
}

void ropme(){
  char fullbuffer[20];
  read(0,&fullbuffer,200);
}

int main(){
  daily();
  ropme();
  return 0;
}
