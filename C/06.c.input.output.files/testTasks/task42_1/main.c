#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	
	struct info_t 
	{
		uint32_t id;
		uint32_t nothing;
		uint32_t start;
		uint32_t finish;
	};
	
	struct stat st;
	stat(argv[1], &st);
	if (st.st_size % (4 * sizeof(uint32_t)) != 0)
	{
		errx(2, "wrong file size");
	}

	int fd = open(argv[1], O_RDONLY);
	
	struct info_t info;

	uint32_t avg;
	int cnt = 0;
	while (read(fd, &info, (4*sizeof(uint32_t))))
	{
		cnt++;
		avg = avg + info.finish - info.start;
	}
	
	avg = avg / cnt;

	uint32_t disp = 0;
	
	lseek(fd, 0, SEEK_SET);
	
	while(read(fd, &info, (4*sizeof(uint32_t))))
	{
		disp = disp + (info.finish - info.start - avg) * (info.finish - info.start - avg);
	}	

	disp = disp / cnt;
	lseek(fd, 0, SEEK_SET);
	printf("disp: %d\n", disp);
    
	while(read(fd, &info, (4*sizeof(uint32_t))))
    {
		uint32_t duration = (info.finish - info.start) * (info.finish - info.start);
		
		if (duration >= disp)
		{
			printf("id: %d, dur: %d\n", info.id, duration);
		}
	}
}
