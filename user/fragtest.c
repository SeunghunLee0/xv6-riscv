#include "kernel/types.h"
#include "user/user.h"

int main(void) {
  void *a = malloc(28);
  void *b = malloc(44);
  void *c = malloc(60);
  (void)a; (void)b; (void)c;

  printf("frag bytes now: %lu\n", frag_bytes());
  exit(0);
}
