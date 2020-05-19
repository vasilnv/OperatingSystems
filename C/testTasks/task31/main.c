#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <stdlib.h>
#include <fcntl.h>

#include <unistd.h>

int cmp(const void* a, const void* b)
{
	return *((unsigned char*) a) - *((unsigned char*)b);
}

int main (int argc, char* argv[])
{
	if (argc != 3) 
	{
		errx(1, "wrong number of parameters");
	}
	
	int fd1;
	int fd2;

	if( (fd1 = open (argv[1], O_RDONLY)) == -1 )
	{
		err(2, "failed to open file %s", argv[1]);
	}
	
	if( (fd2 = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR)) == -1 )
    {
		close(fd1);
        err(3, "failed to open file %s", argv[2]);
    }

	struct stat st;
	
	if ( stat(argv[1], &st) == -1 )
	{
		err(4, "failed to stat file %s", argv[1]);
	}
	
	if (st.st_size == 0) 
	{
		close(fd1);
		close(fd2);
		exit(0);
	}

	void *buf = malloc(st.st_size);
	
	if(!buf)
	{
		int olderrno = errno;
		close(fd1);
		close (fd2);
		errno=olderrno;
		err(5, "no memory");
	}
	
	if ( read(fd1, buf, st.st_size) != st.st_size )
	{
        int olderrno = errno;
        free(buf);
		close(fd1);
        close (fd2);
		errno=olderrno;
		err (5, "error while reading file %s", argv[1]);
	}
	
	qsort(buf, st.st_size, 1, cmp);
	
	if ( write(fd2, buf, st.st_size) != st.st_size)
	{
		int olderrno = errno;
        free(buf);
		close(fd1);
        close (fd2);
        errno=olderrno;
        err(6, "error while writing file %s", argv[2]);
	}
	
	free(buf);
	close(fd1);
	close(fd2);
	exit(0);
}