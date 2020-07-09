#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>

int main(int argc,char** argv)
{
	if(argc < 3)
	{
		errx(1,"invalid args");
	}

	time_t dur = *argv[1]-'0';
	char* cmd = argv[2];
	
	time_t start = time(NULL);
	int cnt=0;
	
	int fd=open("run.log", O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR);
	
	while(1)
	{
		pid_t p = fork();
		int status;
		if( p == 0)
		{
			if (execvp(cmd,argv + 2) < 0)
			{
				return 1;
			}
		}
		else if(p < 0)
		{
			err(3,"Failed fork");
		}
		
		wait(&status);
		
		int exitstatus=WEXITSTATUS(status);	

		if (exitstatus != 0)
		{
			cnt++;
			if (cnt == 2)
			{
				break;
			}
		}
		
		time_t end = time(NULL);
		printf("%ld %ld %ld\n", start, end, dur);
		
		char buff [3*sizeof(intmax_t) + 4];
		//buff = start + ',' + end + ',' + exitstatus;
		
		sprintf(buff,"%jd,%jd,%d\n",(intmax_t)start,(intmax_t)end,exitstatus);

		write(fd, &buff, sizeof(buff));
		if(end - start > dur)
		{
			cnt++;
			if (cnt == 2)
			{
				break;
			}
		}	
		
	}
	exit(0);	
}