#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc != 2) 
	{
		errx(2, "one argument expected");
		exit (-1);
	}
	
	int fd;
	if ((fd = open(argv[1], O_RDONLY)) == -1) 
	{
		errx(2, "File failed to read successfully");
	}
	
	char c;
	int words = 0;
	int chars = 0;
	int lines = 0; 
	while (read(fd, &c, 1))
	{
		chars ++;
		if (c == '\n')
		{
			words ++;
			lines ++;
		}
		if(c == ' ' || c == '\t')
		{
			words ++;
		}
	}

	printf("File has %d characters, %d words, %d lines ", chars, words, lines);
	close(fd);
	exit(0);
}
