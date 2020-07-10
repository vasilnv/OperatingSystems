//find .. -type f -printf "%f %T@\n" | sort -n -t ' ' -k2 | tail -n 1 | cut -d ' ' -f2
//								   1 | 0	1 | 0		1 | 0
#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	
	int a[2];
	if (pipe(a) < 0 )
	{
		err(2, "failed to pipe");
	}
	
	pid_t pid = fork();
	if (pid < 0)
	{
		err(3, "failed to fork");
	}
	
	if (pid == 0)
	{
		close(a[0]);
		if (dup2(a[1],1) < 0)
		{
			err(7, "failed to dup2");
		}
	
		if(execlp("find", "find", argv[1], "-type", "f", "-printf", "%f %T@\n",(char*)NULL) < 0)
		{
			err(4, "failed to exec find");
		}
	}
	wait(NULL);
	close(a[1]);
	
	int b[2];
	if (pipe(b) < 0)
	{
		err(8, "failed to pipe");
	}
	
	pid=fork();
	if (pid < 0)
	{
		err(9, "failed to fork");
	}
	if (pid == 0)
	{
		close(b[0]);
		if (dup2(a[0],0) < 0)
		{
			err(10, "failed to dup");
		}
		if (dup2(b[1],1) < 0)
		{
			err(11, "failed to dup");
		}
	
		if(execlp("sort", "sort", "-n", "-t", " " ,"-k2", (char*)NULL) < 0)
		{
			err(5, "failed to exec sort");
		}
	}
	
	wait(NULL);
	close(b[1]);
		
	int c[2];
	if (pipe(c) < 0)
	{
		err(12, "failed to pipe");
	}
	
	pid=fork();
	if (pid < 0)
	{
		err(13, "failed to fork");
	}
	if (pid == 0)
	{
		close(c[0]);
		dup2(b[0],0);
		dup2(c[1],1);

		if (execlp("tail", "tail", "-n", "1"))
		{
			err(6, "failed to exec tail");
		}
	}
	
	wait(NULL);
	close(c[1]);
	
	if(dup2(c[0],0) < 0)
	{
		err(14, "failed to dup");
	}
	
	if(execlp("cut", "cut", "-d", " ", "-f1", (char*)NULL) < 0)
	{
		err(15, "failed to exec cut");
	}

	exit(0);
}
