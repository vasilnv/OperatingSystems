#include <sys/types.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
	while(1)
	{
		write(1, "enter command: ", 15);
		char buff[1024];
	
		read(0, &buff, sizeof(buff));
		buff[strlen(buff) - 1] = '\0';
		
		if (strcmp(buff, "exit") == 0)
		{
			break;
		}
		
		pid_t pid = fork();	


		if (pid == 0)
		{
			if (execlp(buff, buff, (char*)NULL) < 0)
			{
				err(1,"failed to exec command");
			}
		}
		wait(NULL);
	}



}