#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <err.h>
#include <sys/wait.h>
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);
	
	if (write(fd, "fo", 2) != 2)
	{
		err(2, "failed to write");
	}
	
	int p = fork();
	if (p == 0)
	{
		if(write(fd, "bar", 3) != 3)
		{
			err(3, "child failed to write in file");
		}
	}
	else if (p > 0)
	{
		wait(NULL);
		if(write(fd, "o\n", 2) != 2)
		{
			err(4, "parent failed to write in file");
		}
	}

	exit(0);
}
