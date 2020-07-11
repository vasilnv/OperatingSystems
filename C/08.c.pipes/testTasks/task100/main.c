//cat /etc/passwd | grep ^grade | sort
// 				1 | 0	  	  1 | 0
#include <err.h>
#include <unistd.h>
#include <sys/types.h>


int main()
{
	int a[2];
	if (pipe(a) < 0)
	{
		err(1, "failed to pipe");
	}
	
	int pid=fork();
	if (pid < 0)
	{
		err(7, "failed to pipe");
	}
	else if (pid == 0)
	{
		close(a[0]);
		if (dup2(a[1],1) < 0)
		{
			err(2, "failed to dup");
		}
	
		if (execlp("cat", "cat", "/etc/passwd", (char*)NULL) < 0)
		{
			err(3, "failed to exec cat");
		}
	}
	
	close(a[1]);
	
	int b[2];
	if (pipe(b) < 0)
	{
		err(8, "failed to pipe");
	}
	
	pid=fork();
	
	if(pid < 0)
	{
		err(4, "failed to fork");
	}
	else if (pid == 0)
	{
		close(b[0]);
		if (dup2(a[0],0) < 0)
		{
			err(9, "failed to dup");
		}
		
		if (dup2(b[1],1) < 0)
		{
			err(10, "failed to dup");
		}
	
		if (execlp("grep", "grep", "^grade", (char*)NULL) < 0)
		{
			err(5, "failed to exec grep");
		}
	}
	
	close(b[1]);
	
	if (dup2(b[0],0) < 0)
	{
		err(11, "failed to dup");
	}
	
	if(execlp("sort", "sort", (char*)NULL) < 0)
	{
		err(6, "failed to exec sort");
	}
}