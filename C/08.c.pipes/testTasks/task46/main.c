#include <err.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	char* cmd = {"echo"}; 
	if (argc == 2)
	{
		cmd = argv[1];
	}
	
	if (argc != 1 && argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	
	char param1[5];
	char param2[5];
		
	while(1)
	{
		char c;
		int n = 1;
		int cnt = 0;
		param1[0]='\0';
		param2[0]='\0';
		while(read(0, &c, 1))
		{
			if (c == '\0')
			{
				break;
			}
			if (c != '\n' && c != ' ')
			{
				if(n == 1)
				{
					param1[cnt]=c;
					cnt++;
				}
				else
				{
					param2[cnt]=c;
					cnt++;
				}
			}
			else if (c == '\n' || c == ' ')
			{
				if (n == 1)
				{
					param1[cnt]='\0';
					cnt = 0;
					n++;
				}
				else if (n == 2)
				{
					param2[cnt]='\0';
					break;
				}
			}
		}
		
//		printf("cmd: %s, param1: %s, param2: %s\n,",cmd,param1,param2);
		if (param1[0] == '\0')
		{
			break;
		}
		int pid = fork();
		if (pid == 0)
		{
			if (*param1 != '\0' && *param2 != '\0')
			{
				execlp(cmd, cmd, param1, param2, (char*)NULL);
			}
			else if (*param1 != '\0')
			{
				execlp(cmd, cmd, param1, (char*)NULL);
			}
			else
			{
				execlp(cmd, cmd, (char*)NULL);
			}
		}
		wait(NULL);
	}

}