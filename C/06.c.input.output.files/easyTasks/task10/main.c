#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[] )
{
    if (argc != 2)
    {
        errx(1, "only 1 parameter needed");
    }

    int fd;
    if ( (fd = open(argv[1], O_RDWR)) < 0 )
    {
        err(2, "failed to open");
    }

    uint8_t c;
    uint8_t max;
    ssize_t read_size;
    while((read_size = read(fd, &c, 1)) == 1)
    {
        if (c > max)
        {
            max = c;
        }
    }

    printf("%x\n", max);
}
