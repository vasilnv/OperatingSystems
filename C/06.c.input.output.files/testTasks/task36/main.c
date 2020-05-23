#include <err.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{	

	int fd;
	char c;
	if (argc == 1)
	{	
		ssize_t read_size;
		while((read_size = read(0, &c, 1)) > 0) 
		{
			if (read_size != 1)
			{
				err(1, "failed to read from stdin");
			}
		
			if (write(1, &c, 1) != 1) 
			{
				err(2, "failed to write to stdout");
			}
		}
		exit(0);
	}
	if (strcmp(argv[1], "-n") != 0)
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "-") == 0)
			{
				fd = 0;
			}
			else
			{
				fd = open (argv[i], O_RDONLY);
			}
			while (read(fd, &c, 1) > 0)
			{
				write (1, &c, 1);
			}
		}	
	}
	else
	{
    	setbuf(stdout, NULL);
		uint8_t cnt = 1;
		for (int i = 2; i < argc; i++)
		{
	        if (strcmp(argv[i], "-") == 0)
            {   
                fd = 0;
            }
            else
            {   
                fd = open (argv[i], O_RDONLY);
            }

			int new = 1; 
			while (read(fd, &c, 1) > 0)
            {
				if(new)
				{
                    printf("\t %d ", cnt);
                    cnt++;
                	write (1, &c, 1);
					new = 0;
				}
			    else { 
					write (1, &c, 1);
			 	}
				if(c == '\n')
				{
					new = 1;
				}

			}
		}
	}

	if (fd == 0)
	{
		close(fd);
	}
	exit(0);
}


/*
pseudcode
	argc == 1
		read(0, ....);
		write
	argc > 1
		if argv[1] == -n
		row = 0;
		i = 1;
	i = 0;
	while(i < argc)
		if ( argv[i] == '-')
			read(0, ...)
			write(1, ...)
		else
			fd=open(argv[i], ...)
			read(fd, ...);
			write(fd, ...);
*/