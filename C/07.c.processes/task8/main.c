#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <err.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	
	int fd = open(argv[1], O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	
	int p = fork();
	int status;
	if (p < 0)
	{
		err(2, "failed to fork");
	}
	else if (p > 0)
	{
		wait(&status);
		char c;
		if (read (fd, &c, sizeof(c)) < 0)
		{
			err(3, "failed to read");
		}
		if (write (1, &c, sizeof(c)) < 0)
		{
			err(4, "failed to write");
		}
		while (read (fd, &c, sizeof(c)) > 0)
		{	
			if (write (1, " ", 1) < 0 )
			{
				err(5, "failed to write");
			}
			if (write (1, &c, sizeof(c)) < 0 )
			{
				err(6, "failed to write");
			}
     	}
	}
	else
	{
		char* str = "foobar";
		write(fd, str, strlen(str));
		lseek(fd, 0, SEEK_SET);
	}

	exit(0);
}
