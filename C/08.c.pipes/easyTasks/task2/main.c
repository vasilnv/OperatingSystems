// cat /etc/passwd | cut -d ':' -f 7 | sort | uniq
// cut can work with files
// so we can make it cut -d ':' -f 7 /etc/passwd | sort | uniq

#include <unistd.h>
#include <sys/types.h>
#include <err.h>
#include <stdlib.h>
int main()
{
	int a[2];
	pipe(a);
	pid_t p = fork();
	if (p < 0) 
	{
		err(2, "failed to fork");
	}
	
	if (p == 0) 
	{
		close(a[0]);
	
		if (dup2(a[1],1) < 0) 
		{
			err(3, "failed to dup");
		}
		if (execlp("cut", "cut", "-d", ":", "-f", "7", "/etc/passwd", (char*)0) < 0)
	{
		err(4, "failed to execlp");
	}
		//execlp("cut", "cut", "-d:", "-f7", "/etc/passwd", (char*)0); also possible
	}
	close(a[1]);
	int b[2];
	if(pipe(b) < 0)
	{
		err(5, "failed to make pipe b");
	}
	
	p = fork();
	if ( p < 0)
	{
		err (6, "failed to fork");
	}
	
	if (p == 0) 
	{
		if (dup2(a[0], 0) < 0)
		{
			err(7, "failed to dup");
		}
		close(b[0]);
		if ( dup2(b[1],1) < 0 ) 
		{
			err(8, "failed to dup");
		}
		if (execlp("sort", "sort", (char*)0) < 0 )
		{
			err(9, "failed to execlp");
		}
	}
	
	close (b[1]);
	if (dup2(b[0], 0) < 0 )
	{
		err(10, "failed to dup");
	}
	if (execlp ("uniq", "uniq", (char*)0) < 0 )
	{
		err(11, "failed to execlp");
	}
	exit(0);
}
