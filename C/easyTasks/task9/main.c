#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdint.h>

#include <unistd.h>
#include <err.h>
#include <stdlib.h>

#include <string.h>
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong number of parameters");
	}

	if(strcmp(argv[1], "--print") != 0 && strcmp(argv[1], "--min") != 0 && strcmp(argv[1], "--max") != 0) 
	{
		errx(2, "wrong parameter");		
	}	
	
	int fd = open (argv[2], O_CREAT | O_RDONLY);
	if (fd < 0) 
	{
		err(2, "error occured when opening file");
	}	

	struct stat st;
	if(stat(argv[2], &st) == -1)
	{
		err(3, "error stat");		
	}
	
	if (st.st_size == 0)
	{
		err(4, "file is empty");
		exit(0);
	}

	

	uint16_t cnum;
	uint16_t* all = malloc(st.st_size);
	ssize_t read_size;

	int i=0;
	while ( (read_size = read(fd, &cnum, sizeof(uint16_t))) > 0 )
	{
		if (read_size > (ssize_t)sizeof(uint16_t))
		{
			errx(1, "error while reading");
		}
		all[i] = cnum;
		i++; 
	}
	uint16_t min = 0x9999;
	uint16_t max = 0;
	for (int j = 0; j < i; j++)
	{
		if(strcmp(argv[1], "--print") == 0 ) 
		{
			printf("%x\n", all[j]);
		}
		else
		{
			if ( all[j] < min)
			{
				min = all[j];
			}
			if (all[j] > max)
			{
				max = all[j];
			}
		}
	}
	if(strcmp(argv[1], "--min") == 0)
	{
		printf("%x\n", min);
	}
	if(strcmp(argv[1], "--max") == 0)
	{
		printf("%x\n", max);
	}
	free(all);
	close(fd);
	exit(0);
}
