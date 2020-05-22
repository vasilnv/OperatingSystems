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
	if (argc != 5)
	{
		errx(1, "Usage: ./main f1.dat f1.idx f2.dat f2.idx");
	}	
	
	struct stat st;
	if (stat(argv[2], &st) < 0)
	{
		err(2, "failed to stat");
	}
	
	struct entry_t
	{
		uint16_t pos;	
		uint8_t len;
		uint8_t nothing;
	};
	
	if (st.st_size % sizeof(struct entry_t) != 0)
	{	
		errx(3, "wrong length of file f1.idx");
	}	

	if (stat(argv[1], &st) < 0)
	{
		errx(4,"cannot stat f1.dat");
	}
	
	if (st.st_size > 0xffff)
	{
		warnx("file is too big - more than 0xffff");
	}

	int f1dat = open(argv[1], O_RDONLY);
	if (f1dat < 0)
	{
		err(4, "failed to open f1.dat");
	}

	int f1idx = open(argv[2], O_RDONLY);
	if (f1idx < 0)
	{
		err(5, "failed to open f1.idx");
	}

	int f2dat = open(argv[3], O_RDWR | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);
	if (f2dat < 0)
	{
		err(6, "failed to open f2.dat");
	}

    int f2idx = open(argv[4], O_RDWR | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);
    if (f2idx < 0)
    {
        err(7, "failed to open f2.idx");
    }
	
	struct entry_t entry;
	ssize_t read_size;
	struct entry_t y;
	y.pos = 0;
	y.len = 0;
	y.nothing = 0;
	
	while ((read_size = read(f1idx, &entry, sizeof(entry))) > 0)
	{
		if(read_size != sizeof(entry))
		{
			int olderrno = errno;
			close(f1dat);
			close(f1idx);
    		close(f2dat);
	    	close(f2idx);
			errno = olderrno;
			err(8, "failed to read");
		}
		uint8_t a;
		if (lseek(f1dat, entry.pos, SEEK_SET) < 0)
		{
			int olderrno = errno;
            close(f1dat);
            close(f1idx);
            close(f2dat);
            close(f2idx);
            errno = olderrno;
			err(9, "failed to lseek to %d in %s", entry.pos, argv[1]);
		}
		if (read(f1dat, &a, sizeof(a)) < 0 )
		{
            int olderrno = errno;
            close(f1dat);
            close(f1idx);
            close(f2dat);
            close(f2idx);
            errno = olderrno;
            err(9, "failed to read from f1.dat");

		}
	
		if (a >= 'A' && a <= 'Z')
		{
			char* c = malloc(entry.len);
			lseek(f1dat, -1*sizeof(a), SEEK_CUR);
			if (read (f1dat, c, entry.len) < 0)
			{
				err(10, "failed to read from f1.dat");
			}
			if (write (f2dat, c, entry.len) != entry.len)
			{
				err(11, "failed to write in f2.dat");
			}
		
			y.len = entry.len;
			y.nothing = 0;

			if (write(f2idx, &y, sizeof(y)) != sizeof(y))
			{
	            int olderrno = errno;
	            close(f1dat);
    	        close(f1idx);
        	    close(f2dat);
            	close(f2idx);
            	errno = olderrno;
            	err(10, "failed to write in f2.idx");
			}
			
			y.pos += y.len;	
		}
		
	}
	
	
	close(f1dat);
	close(f1idx);
	close(f2dat);
	close(f2idx);
	exit(0);
}

/*
pseudocode
	input:
		f1.dat (uint8_t/char)
		f1.idx	
			-uint16_t	pos
			-uint8_t	len
			-uint8_t	nothing
	output:
		f2.dat
		f2.idx

	struct entry_t
	{
		uint16_t pos
		uint8_t	len
		uint8_t	nothing
	}	

	f1.idx.size % sizeof(struct entry_t);
	warn: if f1.dat.size > 655535	
	
	foreach X in f1.idx
		if string defined by X matches A-Z
			write string in f2.dat
			write proper entry in f2.idx
	
	read f1.idx	
*/
