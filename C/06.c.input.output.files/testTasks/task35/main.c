#include <err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	if(argc != 4)
	{
		errx(1, "Usage ./main f1.bin f2.bin patch.bin");
	}
	
	int fd1 = open(argv[1], O_RDONLY);
	if (fd1 < 0)
	{
		err(2, "failed to open file %s", argv[1]); 
	}
	
	int fd2 = open(argv[2], O_RDONLY);
	if (fd2 < 0)
	{
		err(3, "failed to open file %s", argv[2]);
	}
	
	struct patch
	{
		uint16_t offset;
		uint8_t orig;
		uint8_t new;
	};
	
	int fd3 = open(argv[3], O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	if (fd3 < 0)
	{
		err(4, "failed to open patch file");
	}
	
	char c1;
	char c2;
	struct patch p;
	int cnt = 0;
	ssize_t read_size1;
	ssize_t read_size2;
	while( (read_size1 = read(fd1, &c1, sizeof(c1)) ) > 0 && (read_size2 = read(fd2, &c2, sizeof(c2)) ) > 0)
	{
		if (read_size1 != sizeof(c1))
		{
			int olderrno = errno;
			close(fd1);
			close(fd2);
			close(fd3);
			errno = olderrno; 
			err(5, "failed to read from %s\n", argv[1]);
		}

        if (read_size2 != sizeof(c2))
        {
            int olderrno = errno;
            close(fd1);
            close(fd2);
            close(fd3);
            errno = olderrno;
            err(6, "failed to read from %s\n", argv[2]);
        }

		if (c1 != c2)	
		{
			p.offset = cnt;
			p.orig = c1;
			p.new = c2;

			if (write(fd3, &p, sizeof(p)) != sizeof(p) )
			{
		        int olderrno = errno;
	            close(fd1);
    	        close(fd2);
        	    close(fd3);
           		errno = olderrno;
           		err(7, "failed to write in %s\n", argv[3]);
			}
		}
		cnt++;
	}
}


/*
pseudocode
	input files:
		f1.bin
		f2.bin
	outputfiles:
		patch.bin
			-uint16_t offset
			-uint8_t original
			-uint8_t new
	
	struct patch
	{
            uint16_t offset
            uint8_t original
            uint8_t new
	}
	
	int cnt;
	while ( read f1 && read f2 )
	{
		if c1 != c2
			patch.offset = cnt;
			patch.original = c1;
			patch.new = c2;
	}
*/