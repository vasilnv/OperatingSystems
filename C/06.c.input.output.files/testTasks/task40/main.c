#include <err.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	if (argc < 3 || argc > 6 )
	{
		errx(1, "wrong number of parameters");
	}

	if(strcmp(argv[1], "-c") == 0)
	{
		if (strlen(argv[2]) == 1)
		{
			int n = *argv[2] - '0';
			char c;
			for (uint8_t i = 0; i < n; i++)
			{
				read(0, &c, 1);
			}

			write(1, &c, 1);
		}
		else if (strlen(argv[2]) == 3)
		{
			int n1 = *argv[2] - '0';
			int n2 = *(argv[2] + 2) - '0';
			char c;

            for (uint8_t i = 1; i < n1; i++)
            {
                read(0, &c, 1);
            }
			
			for (int i = n1; i <= n2; i ++)
			{
	        	read(0, &c, 1); 
			   	write(1, &c, 1);
			}
		}
	}
	
	if(strcmp(argv[1], "-d") == 0 && strcmp(argv[3], "-f") == 0)
	{	
		if(strlen(argv[4]) == 1)
		{
			char c;
			int cnt = 1;
			while(read(0, &c, 1) > 0)
			{
				if (cnt == (*argv[4] - '0') && c != *argv[2])
				{
					write(1, &c, 1);
				}
				if (c == *argv[2])
				{
					cnt++;
				}	
		
			}
		}
		// cut -d '.' -f 3
		if (strlen(argv[4]) == 3)
		{
		    char c; 
            int cnt = 1;
            while(read(0, &c, 1) > 0)
            {   
                if (cnt >= (*argv[4] - '0') && cnt <= (*(argv[4] + 2) - '0') )
                {   
                    write(1, &c, 1);
                }
                if (c == *argv[2])
                {   
                    cnt++;
                }
            
            }

			
		}
	}

	exit(0);
}


/*
pseudocode
	options
		./main 	-c num / num1-num2
				-d c -f num/num1-num2
	input:
		stdin
	output:
		stdout
	
if option == "-c"
	if(num)
		find n and read n times 1 char
		read (0, &n, 1)
		write(1, &n, 1);
	else
		find n1, read n1 times 1 char
		read n2-n1+1 times 1 char
		write n2-n1+1 times 1 char
*/
