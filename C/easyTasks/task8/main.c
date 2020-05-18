#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char* argv[]) 
{
	if ( argc != 2 ) 
	{
		errx(2, "wrong number of parameters");
	}
	
	int fd;
	printf("%s\n", argv[1]);
	if ( (fd = open(argv[1], O_RDWR)) == -1 ) 
	{
		err(2, "File failed to open");
	}
	
	char c;
	int read_size;
	while ((read_size = read(fd, &c, 1)) > 0)
	{
		if ( c == ':')
		{
			c = '?';
			lseek(fd, -1, SEEK_CUR);
			if ( write(fd, &c, 1) != read_size ) 
			{
				close(fd);
				err(2, "error occured while writing");
			}
		}
	}
	exit(0);
}
