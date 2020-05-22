#include <stdlib.h>
#include <err.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>

int main()
{
	struct maker 
	{
		uint16_t a1;
		uint8_t a2;
        uint8_t a3;
        uint16_t b1;
        uint8_t b2;
        uint8_t b3;
	};
	
	struct maker mk;
	mk.a1=0;
	mk.a2=2;
	mk.a3=0;
	mk.b1=5;
	mk.b2=3;
    mk.b3=0;
    int fd = open("file.bin", O_CREAT | O_WRONLY | O_TRUNC , S_IWUSR | S_IRUSR);
	
	if (fd < 0) 
	{
		err(2, "failed to open file file.bin");
	}
	
	if ( write (fd, &mk, sizeof(mk)) != sizeof(mk)) 
	{
		err(3, "error occured when writing to file");
	}
	
	exit(0);
}
