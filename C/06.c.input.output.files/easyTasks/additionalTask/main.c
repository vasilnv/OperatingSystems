#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
		exit(1);
	}
	
	int fd=open(argv[1], O_RDONLY);
	
	if (fd < 0)
	{
		err(2, "failed to open file");
	}
	
	int* letters=malloc(32);
	for (int i = 0; i < 32; i++)
	{
		letters[i] = 0;
	}
	
	char c;
	while(read(fd, &c, 1))
	{
		letters[c-'a']++;
	}
	
	char letter='a';
	int max=0;
	for(int i = 0 ; i < 32; i++)
	{
		if (letters[i] > max)
		{
			max = letters[i];
			letter = i + 'a';
		}
	}

	write(1, &letter, 1);
	write(1, "\n", 1);
	exit(0);
}

