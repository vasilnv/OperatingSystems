#include <err.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

int main()
{
    off_t f1_size;
    off_t f2_size;

    struct stat st;
    if (stat("f1", &st) < 0)
    {
        err(4, "cannot stat");
    }

    f1_size = st.st_size;

    if (stat("f2", &st) < 0)
    {
        err(4, "cannot stat");
    }
    f2_size = st.st_size;

    struct pair_t
    {
        uint32_t x; //start position
        uint32_t y; //length 
    };

    if (f1_size % sizeof(struct pair_t) != 0)
    {
        errx(5, "wrong f1 size");
    }

    if (f2_size % sizeof(uint32_t) != 0)
    {
        errx(6, "wrong f2 size");
    }

	int fd1;
    int fd2;
    int fd3;

    fd1 = open("f1", O_RDONLY);
    if (fd1 < 0)
    {
        err(1, "Cannot open file f1");
    }

    fd2 = open("f2", O_RDONLY);
    if (fd2 < 0)
    {
        int olderrno = errno;
        close(fd1);
        errno = olderrno;
        err(2, "Cannot open file f2");
    }

    fd3 = open("f3", O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
    if (fd3 < 0)
    {
        int olderrno = errno;
        close(fd1);
        close(fd2);
        errno = olderrno;
        err(3, "Cannot open file f3");
    }

    struct pair_t pair;

    while (read(fd1, &pair, sizeof(pair)))
    {
        if ( lseek(fd2, pair.x*sizeof(uint32_t), SEEK_SET) < 0 )
        {
            int olderrno = errno;
            close(fd1);
            close(fd2);
			errno = olderrno;
			err(7, "lseek error");
		}
		
		uint32_t element;
		uint32_t cnt = 0;
		uint32_t len = pair.y;
		
		while(read(fd2, &element, sizeof(element)))
		{
			write (fd3, &element, sizeof(element));
			cnt ++;
			if (cnt == len)
			{
				break;
			}
		}
	}
	
	close(fd1);
	close(fd2);
	close(fd3);
	
	exit(0);
}
