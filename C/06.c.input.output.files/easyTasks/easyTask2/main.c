#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		errx(1, "wrong number of parameters");
		exit(-1);	
	}

	int fd;
	char c;
	
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		errx(1, "File failed to read successfully");
		exit(-1);
	}
	
	int i=0;
	while (read(fd, &c, 1))
	{
		write(1, &c, 1);
		if(c == '\n')
		{
			i = i + 1;
		}
		if(i == 10) 
		{
			break;
		}
	}

	close(fd);
	exit(0);
}
