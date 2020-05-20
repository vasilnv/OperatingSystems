#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int main(int argc, char* argv[])
{
	int fd1;
	int fd2;
	char c;
	
	if ( argc != 3 ) 
	{
		errx(2, "wrong number of parameters");
	}
	
	if ((fd1=open(argv[1], O_RDWR)) == -1) 
	{
		err(2, "error occured while opening file %s", argv[1]);
	}
	
	if ((fd2=open(argv[2], O_RDWR | O_CREAT)) == -1)
    {
		close(fd1);
        err(3, "error occured while opening file %s", argv[2]);
    }
	
	ssize_t read_size;
	
	while (( read_size = read(fd1, &c, 1) > 0 ) )
	{
		if ( write(fd2, &c, 1) != read_size )
		{	
			close(fd1);
			close(fd2);
			err(1, "error occured while writing");
		}
	}
}
