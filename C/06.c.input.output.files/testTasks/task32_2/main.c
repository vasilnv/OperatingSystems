#include <err.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		errx(1, "wrong number of parameters");
	}

	struct stat st1;
	
	stat(argv[1], &st1);
	
	if ( (st1.st_size % (2 * sizeof(uint32_t))) != 0 )
	{
		errx(2, "file has wrong size");
	}
	
	struct stat st2;
	stat(argv[2], &st2);
	
	if ( (st2.st_size % sizeof (uint32_t)) != 0)
	{
		errx(3, "seconf file has wrong size");
	}

	int fd1=open(argv[1], O_RDONLY);
	int fd2=open(argv[2], O_RDONLY);
	int fd3=open("res.bin", O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);

	struct pair_t {
		uint32_t a;
		uint32_t b;	
	};

	struct pair_t pair;	

	while(read(fd1, &pair, sizeof(pair)))
	{
		lseek(fd2, pair.a*sizeof(uint32_t), SEEK_SET);
		uint32_t n;
		for (uint32_t i = 0; i < pair.b; i++)
		{
			read(fd2, &n, sizeof(uint32_t));
			write(fd3, &n, sizeof(uint32_t));
		}
	}
	
	close(fd1);
	close(fd2);
	close(fd3);
	exit(0);
}
