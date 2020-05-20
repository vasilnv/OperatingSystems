#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int fd1;
	int fd2;
	char c;
	
	if ( argc < 3 ) 
	{
		errx(2, "wrong number of parameters");
	}
		
	ssize_t read_size;
	
	for ( int i = 1; i < argc - 1; i ++ ) 
	{
	    if ((fd1=open(argv[i], O_RDWR)) == -1)
	    {
    	    err(2, "error occured while opening file %s", argv[i]);
    	}
		
		char* resdir= malloc ( strlen(argv[argc-1]) + strlen(argv[i]));
		strcpy(resdir, argv[argc-1]);
		printf("%s\n", argv[argc-1]);
		printf("%s\n", resdir);
		strcat(resdir, argv[i]);		
	    if ((fd2=open(resdir, O_RDWR | O_CREAT)) == -1)
	    {
   	    	close(fd1);
        	err(3, "error occured while opening file %s", argv[argc-1]);
    	}

		while (( read_size = read(fd1, &c, 1) > 0 ) )
		{
			if ( write(fd2, &c, 1) != read_size )
			{	
				close(fd1);
				close(fd2);
				err(1, "error occured while writing");
			}
		}
	}
}
