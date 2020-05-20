#include <stdlib.h>
#include <err.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

int main()
{
	struct maker 
	{
		uint16_t a;
		uint16_t b;
		uint16_t c;
		uint16_t d;
	};
	
	struct maker mk;
	mk.a=5;
	mk.b=6;
	mk.c=7;
	mk.d=8;

	int fd = open("file.bin", O_CREAT | O_WRONLY | O_TRUNC , S_IWUSR | S_IRUSR);
	
	if (fd < 0) 
	{
		err(2, "failed to open file file.bin");
	}
	
	if ( write (fd, &mk, sizeof(mk)) != sizeof(mk)) 
	{
		err(3, "error occured when writing to file");
	}
	
	exit(0);
}
