#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/wait.h>
#include <err.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		errx(2, "wrong number of parameters");
	}	

    int a[2];
    pipe(a);

	
	int p = fork();
	if (p < 0)
	{
		err(1, "failed to fork");
	}
	if (p == 0)
	{
		close(a[1]);
		close(0);
		dup2(a[0], 0);
		
		if (execlp("wc", "wc", "-c", (char*)NULL) == -1 )
		{
			err(3, "failed to execlp wc");
		}		
	}	
	
	close(a[0]);
	
	write(a[1], argv[1], strlen(argv[1]));
	
	close(a[1]);
	wait(NULL);
	exit(0);	

}
