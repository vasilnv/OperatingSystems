#include <err.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print_d(const char* arg)
{
	char curr;
	while(read(0, &curr, sizeof(curr)) == sizeof(curr))
	{
		char* ptr = strchr(arg, curr);
		if( ptr == NULL)
		{
			write(1, &curr, 1);
		}
	}
	
	exit(0);
}

void print_s(const char* arg)
{
	char curr;
	char prev;
	int w = 0;
	while(read(0, &curr, sizeof(curr)) == sizeof(curr))
	{
		char* ptr = strchr(arg, curr);
		if (ptr != NULL && w == 0)
		{
			w = 1;
			prev = curr;
			continue;
		}
		if (w == 1)
		{
			if (prev == curr)
			{
				continue;
			}
			else
			{
				write(1, &prev, 1);
			}
		}
		else
		{
			write(1, &curr, 1);
		}
		prev = curr;
	}
	exit(0);
}

void print_no(const char* arg1, const char* arg2)
{
	char c;
	while(read(0, &c, 1) == 1)
	{
		for (size_t i = 0; i < strlen(arg1); i++)
		{
			if (c == arg1[i])
			{
				c = arg2[i];
			}
		}
		
		write(1, &c, 1);
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong num of parameters");
	}
	
	if(strcmp("-d", argv[1]) == 0)
	{
		print_d(argv[2]);
	}
	
	else if (strcmp("-s", argv[1]) == 0)
	{
		print_s(argv[2]);
	}

	print_no(argv[1], argv[2]);
	
	exit(0);	
}


/*
./main 		option	 set1  	set2
0			1		 2 		3 		= 4
			-d		 set1			= 3
			-s		 set1			= 3
			set1	 set2			= 3
input:
	stdin
	option
	set1
	set2	
output:
	stdout

option
	-s
	-d
	-no

if option == d
	read (0, &c, 1)
		if c not in set1
			write(1, &c, 1);

if option == s
int w = 0
char prev
	read (stdin, &c, 1)
		if c in set1 and w == 0 
			w = 1
			prev = c 
			continue			
		if w == 1
			if prev == c
				continue
			else
				write(1, &c, 1);
		else
			write(1,&c, 1)
		prev = c	
		
if no option 
	read from output
		for i = 0 ; i < set size; i++
			if set1[i] == c
				c = set2[i]
			fi
		done
		write (1, &c, 1) 
  
*/