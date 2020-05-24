#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	
	int fd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC , S_IWUSR | S_IRUSR);
	if (fd < 0)
	{
		err(2, "failed to open file");
	}

	int p = fork();	
	if (p < 0)
	{
		err(3, "failed to fork");
	}	
	else if (p > 0)
	{
		wait(NULL); // remove if we want to print either barfoo or foobar
		write(fd, "bar", 3);
	}
	else 
	{
		write(fd, "foo", 3);
	}
}
