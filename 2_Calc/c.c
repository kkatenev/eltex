#include <stdio.h>
#include <stdlib.h>
#include "calc.c"

int main(int argc, char const *argv[]) {
  int a,b,value;

  do {
      get_menu();

      scanf("%d", &value);
      if(value==5)
          {
              printf("Exit success!");
              exit(0);
          }

      printf("\nEnter values\na = ");
      scanf("%d", &a);
      printf("b = ");
      scanf("%d", &b);

      switch (value) {
          case 1:
              printf("%d + %d = %d\n", a, b, act_plus(a, b));
              break;
          case 2:
              printf("%d - %d = %d\n", a, b, act_minus(a, b));
              break;
          case 3:
              printf("%d * %d = %d\n", a, b, act_mult(a, b));
              break;
          case 4:
              printf("%d / %d = %.1f\n", a, b, act_division(a, b));
              break;
          default:
              printf("\nSomething wrong.......\n");
      }
  }
      while (value != 5);

  return 0;
}
