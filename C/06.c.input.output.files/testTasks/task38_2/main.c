#include <err.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong number of parameters");
	}

	char c;
	if (strcmp(argv[1], "-d") == 0)
	{
		while (read(0, &c, 1))
		{
			if (strchr(argv[2], c) == NULL)
			{
				write(1, &c, 1);
			}
		}
	}
	else if (strcmp (argv[1], "-s") == 0)
	{
		read(0, &c, 1);
		char prev = c;
		while (read(0, &c, 1) )
		{	
			if (strchr(argv[2], c) != NULL)
			{
				if (prev != c)
				{
					write(1, &prev, 1);
					prev=c;
				}
				else
				{
					continue;
				}
			}
			else
			{	
				write(1, &prev, 1);
				prev=c;
			}
		}
	}
	else
	{
		while (read(0, &c, 1))
		{
			if (strchr(argv[1], c) != NULL)
			{	
				int offset = strchr(argv[1], c) - &argv[1][0];
				char* s=&argv[2][offset];
				write(1, s, 1);
			}
			else
			{
				write(1, &c, 1);
			}
		}
	}
}
