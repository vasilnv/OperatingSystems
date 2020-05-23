#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		errx(1, "wrong number of parameters");
	}	

	int fdp = open (argv[1], O_RDONLY);
	if(fdp < 0)
	{
		err(2, "failed to open %s", argv[1]);
	}
	printf("%s", argv[1]);
	int fd1 = open (argv[2], O_RDONLY);
	if(fd1 < 0)
	{
		err(3, "failed to open %s", argv[2]);
	}
	
	struct patch_t	{
		uint16_t offset;
		uint8_t org;
		uint8_t new;
	};
	
	struct stat st;
	if(stat(argv[1], &st) < 0)
	{
		err(4, "failed to stat");
	}
	
	if (st.st_size % sizeof(struct patch_t) != 0)
	{
		errx(5, "%s is wrong size", argv[1]);
	}

	struct patch_t patch;
	ssize_t read_size = read(fdp, &patch, sizeof(patch));
	if ((read_size) < 0)
	{
		err(6, "failed to read %s", argv[1]);
	}	

	int fd2 = open(argv[3], O_RDWR | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);
	if (fd2 < 0)
	{
		err(7, "failed to open %s", argv[3]);
	}
	
	uint16_t cnt = 0;
	uint8_t c;
	uint8_t cntPatch = 1;
	while (read(fd1, &c, 1) > 0)
	{
		printf("offset: %d, cnt: %d\n", patch.offset, cnt);
		if (cnt != patch.offset)
		{
			if(write(fd2, &c, 1) < 0 )
			{
				err(8, "failed to write in %s", argv[3]);
			}
		} 
		else
		{
			if (c == patch.org)
			{
				cntPatch++;
				if (write(fd2, &patch.new, 1) < 0)
				{
					err(9, "failed to write in %s", argv[3]);
				}
				if ((ssize_t)(cntPatch * sizeof(patch)) < (ssize_t)st.st_size &&
					read(fdp, &patch, sizeof(patch)) < (ssize_t)sizeof(patch))
				{
					err(10, "failed to read");
				}
			}
		}	
		cnt++;
	}
	
	
	close(fdp);
	close(fd1);
	close(fd2);
	exit(0);
}

/*
input-
	patch
	f1
output
	f2

struct patch_t 
	uint16_t offset
	uint8_t org
	uint8_t new

fdp = open(patch, RDONLY)
fd1 = open(f1, RDONLY)

patch_t patch
read (fdp, &patch, sizeof(patch))
int cnt = 0;

while	
	if cnt < patch.offset 
		cnt++
		char c;
		read(f1, &c, 1);
		write(f2, &c, 1);_
	
	else if cnt == patch.offset
		if org = c;
			wirte new in f2
			patch = read(fdp, &patch, sizeof(patch));
			cnt++
		else errx
*/

