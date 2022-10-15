// gcc callback.c -o callback_test

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int dev = open("/dev/callback", O_RDONLY);

    if (-1 == dev) {
        printf("Open failed\n");
        return -1;
    }
    else {
        printf("Open ok\n");
    }

    close(dev);

    exit(0);
}