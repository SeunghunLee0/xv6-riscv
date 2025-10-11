#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define KB 1024
#define MB (1024*1024)

static int sizes[] = {28, 44, 60, 76, 92, 108, 124, 140};

int
main(int argc, char *argv[])
{
  int target_mb = 64;
  if (argc >= 2) {
    int v = atoi(argv[1]);
    if (v >= 1 && v <= 120) target_mb = v;
  }

  int total_bytes_target = target_mb * MB;

  int max_allocs = total_bytes_target / 16 + 1024;
  void **ptrs = (void**) malloc(sizeof(void*) * max_allocs);
  if (!ptrs) {
    printf("memdrive: pointer array alloc failed\n");
    exit(1);
  }

  int n_sizes = sizeof(sizes)/sizeof(sizes[0]);
  int idx = 0, cnt = 0, allocated_sum = 0;


  while (allocated_sum < total_bytes_target && cnt < max_allocs) {
    int req = sizes[idx % n_sizes];
    void *p = malloc(req);
    if (!p) break;

    ((char*)p)[0] = 1;

    ptrs[cnt++] = p;
    allocated_sum += req;
    idx++;
  }

  printf("memdrive: requested ~%d MB in small chunks\n", target_mb);
  printf("memdrive: allocations=%d, requested_sum=%d bytes\n", cnt, allocated_sum);
  printf("memdrive: fragmented bytes (malloc mode): %lu\n", frag_bytes());

  for (int i = 0; i < cnt; i += 2) {
    free(ptrs[i]);
    ptrs[i] = 0;
  }
  printf("memdrive: fragmented bytes after partial free: %lu\n", frag_bytes());

  for (int i = 0; i < cnt; i++) {
    if (ptrs[i]) free(ptrs[i]);
  }
  free(ptrs);

  printf("memdrive: fragmented bytes after full free: %lu\n", frag_bytes());
  exit(0);
}
