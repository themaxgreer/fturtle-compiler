#include <stdio.h>
#include <stdlib.h>

int home(void) {
  printf("H\n");
  return 0;
}

int pushstate(void) {
  printf("[\n");
  return 0;
}

int popstate(void) {
  printf("]\n");
  return 0;
}

int pendown(int flag) {
  printf("%c\n", flag ? 'D' : 'U');
  return 0;
}

int move(double dist) {
  printf("M %13.10f\n", dist);
  return 0;
}

int rotate(double angle) {
  printf("R %13.10f\n", angle);
  return 0;
}

extern int tmain(void);

int main(void) {
  tmain();
  return 0;
}
