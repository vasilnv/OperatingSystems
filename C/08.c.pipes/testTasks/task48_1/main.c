#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[])
{
	int start = time(NULL);
	if (argc < 3)
	{
		errx(1, "wrong number of parameters");
	}
		
	int fd=open("run.log", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	int dur = *argv[1] - '0';
	while(1)
	{
		int status;
		pid_t pid=fork();
		if (pid == 0)
		{
			if(execvp(argv[2], argv + 2) < 0)
			{
				err(2, "failed to exec command");
			}
		}
		wait(&status);

		int end = time(NULL);
		int currDur = end - start;		
		int errcode=WEXITSTATUS(status);


		char buff[24];
		sprintf(buff, "%d,%d,%d\n", start, end, errcode);	
		write(fd, &buff, sizeof(buff));
		if (currDur > dur)
		{
			close(fd);
			break;
		}
		
		if (errcode != 0)
		{
			close(fd);
			break;
		}
	}
	exit(0);
}
