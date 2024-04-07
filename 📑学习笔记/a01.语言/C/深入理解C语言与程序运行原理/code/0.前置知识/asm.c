#include <stdio.h>
int main(void) {
  register long long num asm("rax") = 0x100000000;
  //asm("movl $0x1, %eax");
  asm("movw $0x1, %ax");
  printf("%lld\n", num);
  return 0;
}