// cut -d: -f7 /etc/passwd | sort | uniq -c | sort -n
//						1  | 0	1 | 0	  1 | 0	
#include <stdlib.h>
#include <err.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int a[2];

	if( pipe(a) < 0 )
	{
		err(1,"Failed pipe");
	}
	
	pid_t pid = fork();
	
	if( pid == 0)
	{
		close(a[0]);
		dup2(a[1],1);
		
				
		//write(a[1],&buf,sizeof(buf));

		if(execlp("cut","cut","-d:","-f7","/etc/passwd",(char*) NULL) < 0)
		{
			err(2, "failed cut exec");
		}
		
	}	

	wait(NULL);	
	close(a[1]);	
	
	int b[2];	
	pipe(b);
	pid = fork();
	
	if (pid == 0)
	{
		close(b[0]);
		dup2(a[0],0);
		dup2(b[1],1);
		
		if (execlp("sort", "sort", (char*)NULL) < 0)
		{
			err(3, "failed sort exec");
		}
	}
	wait(NULL);
	close(b[1]);
	
	int c[2];
	pipe(c);
	
	pid = fork();
	
	if (pid == 0)
	{
		close(c[0]);
		dup2(b[0], 0);
		dup2(c[1], 1);
	
		if (execlp("uniq", "uniq", "-c", (char*)NULL) < 0)
		{
			err(4, "failed uniq exec");
		}
	}
	
	close(c[1]);
	
	dup2(c[0],0);
	
	if (execlp("sort", "sort", "-n", (char*)NULL))
	{
		err(5, "failed sort -n exec");
	}
		
	exit(0);

}
