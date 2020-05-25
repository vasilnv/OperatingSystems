#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <errno.h>
int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	
	char* str = argv[1];
	
	int a[2];
	
	if (pipe(a) == -1)
	{
		err(2, "failed to pipe");
	}

	int p = fork();
	// child --------> parent
	//	a[1]          a[0]
	if(p < 0)
	{
		err(3, "failed to fork");
	}
	if (p == 0 )
	{
 		close(a[1]);
    	char c;
    	
		while(read(a[0], &c, 1) > 0)
    	{
        	if (write(1, &c, 1) != 1)
        	{
            	int olderrno = errno;
            	close(a[0]);
            	errno = olderrno;
            	err(5, "failed to write in stdout");
        	}
    	}
		close(a[0]);
		exit(0);
	}
	
    
	close(a[0]);
    
	if(write(a[1], str, strlen(str)) != (ssize_t)strlen(str))
    {
    	int olderrno = errno;
	    close(a[1]);
        errno = olderrno;
        err(4, "failed to write in pipe");
    }

	close(a[1]);
	wait(NULL);
	exit(0);
}