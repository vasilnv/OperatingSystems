#include <err.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

int cmp(const void* a, const void* b)
{
	if (*((uint16_t*) a) > *((uint16_t*)b) )
	{
		return 1;
	}
	else if ( *((uint16_t*)a) < *((uint16_t*) b)  )
	{
		return -1;
	}
	return 0;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong num of parameters");
	}
	
	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		err(2, "failed to open %s", argv[1]);
	}
	
	struct stat st;
	if (stat(argv[1], &st) < 0)
	{
		err(3, "failed to stat %s", argv[1]);
	}
	uint16_t* p = (uint16_t*)malloc(st.st_size);
	if(!p)
	{
		err(4, "failed to malloc");
	} 
	if (read(fd1, p, st.st_size) < 0) 
	{
		err(5, "failed to read");
	}
	
	qsort(p, st.st_size / sizeof(uint16_t), sizeof(uint16_t), cmp);
	
	int fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	write (fd2, p, st.st_size);

	free(p);
	close(fd1);
	close(fd2);
	exit(0);
}
