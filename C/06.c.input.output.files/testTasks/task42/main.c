#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		errx(1, "wrong number of parameters");
	}
	
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		err(2, "failed to open file");
	}
	
	struct el
	{
		uint32_t uid;
		uint16_t not1;
		uint16_t not2;
		uint32_t beg;
		uint32_t end;
	};	

	struct stat st;
	if (stat(argv[1], &st) < 0)
	{
		err(3, "failed to stat");
	}

	if ( st.st_size % sizeof(struct el) != 0)
	{
		errx(4, "the file has wrong size");
	}
	
	struct el e;
	uint32_t sum = 0;
	uint32_t cnt = 0;
	while (read(fd, &e, sizeof(e)))
	{
		sum += (e.end - e.beg) * (e.end - e.beg);
		cnt ++;
	}
	
	int fd2 = open("res.bin", O_WRONLY | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);

	uint32_t d = sum / cnt;
	printf("%d\n", d);	
	lseek(fd, 0, SEEK_SET);

	while (read (fd, &e, sizeof(e)))
	{
		if ((e.end - e.beg) * (e.end - e.beg) > d)
		{
			write (fd2, &e.uid, sizeof(e.uid));
		}
	}
		
	close(fd);
	close(fd2);
	exit(0);
}
