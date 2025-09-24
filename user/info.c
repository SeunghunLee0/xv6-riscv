#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
int pages = freec();
int mb = (pages * 4096) / (1024*1024);

printf("free pages: %d, free mem ~= %d MB\n", pages, mb);
exit(0);
}
