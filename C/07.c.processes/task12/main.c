#include <string.h>
#include <err.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		errx(1, "wrong number of parameters");
	}
	
	int fd = open (argv[3], O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		err(2, "failed to open file");
	}
	
	for (int i = 1; i < argc - 1; i++)
	{	
		int status;
		if (fork() > 0)
		{
			wait(&status);
			if (status == 0)
			{
				write(fd, argv[i], strlen(argv[i]));
				write(fd, "\n", 1);
			}	
		}
		else
		{
			if (execlp(argv[i], argv[i], (char*)NULL) == -1)
			{
				err(3, "failed to exec %s", argv[i]);
			}
		}
	}

	exit(0);

}