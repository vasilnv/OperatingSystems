// cat file | sort | head -n 10
//		  1 | 0  1 | 0

#include <err.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		err(1, "wrong number of parameters");
	}

	int a[2];
	if (pipe(a) == -1 )
	{
		err(4, "failed to pipe");
	}

	int p = fork();
	if (p < 0)
	{
		err(2, "failed to fork");
	}
	
	else if (p == 0)
	{
		close(a[0]);
		if (dup2(a[1], 1) == -1 )
		{
			err(5, "failed to dup");
		}		
		if (execlp("cat", "cat", argv[1], (char*)NULL) == -1 )
		{
			err(6, "failed to exec cat cmd");
		}
	}
	
	close(a[1]);

	int b[2];
	if (pipe(b) == -1)
	{
		err(7, "failed to pipe");
	}

	int p2 = fork();
	if (p2 < 0)
	{
		err(3, "failed to fork");
	}
	
	else if(p2 == 0)
	{
		if (dup2(a[0], 0) == -1 )
		{
			err(8, "failed to dup");
		}
		close(b[0]);
		if (dup2(b[1], 1) == -1)
		{
			err(9, "failed to dup");
		}

		if (execlp("sort", "sort", (char*)NULL) == -1 )
		{
			err(10, "failed to exec sort command");
		}
	}
	close (b[1]);

	if (dup2(b[0], 0) == -1)
	{
		err(11, "failed to dup");
	}

	if (execlp ("head", "head", "-n", "10", (char*)NULL) == -1 )
	{
		err(12, "failed to exec head cmd");
	}

}
