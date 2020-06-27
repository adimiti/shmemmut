#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <stdlib.h>

#include "shmempub.h"


int main(int argc, char *argv[])
{
    char *addr;
    addr = pvtmMmapAlloc("/tmp/mmapfile", 1024, atoi(argv[1]));

    printf("%p - %s\n", addr, addr);

    sprintf(addr, "test:0x%p\n", addr);

    return !addr;
}
