#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

int main(int argc, char* argv[])
{
	if ( argc < 2 ) 
	{
		errx(2, "Invalid number of parameters");
	} 
	
	int fd;
	char c;
	for (int i = 1 ; i < argc ; i ++ ) 
	{
		if (( fd = open(argv[i], O_RDONLY)) == -1 ) 
		{
			err(2, "error occured when trying to open file");
		} 
		
		ssize_t read_size;
		while ((read_size = read(fd, &c, 1)) > 0 ) 
		{
			if (read_size != 1)
			{
				err(2, "error occured when reading file");
			}
			write(1, &c, 1);
		}
	} 
}
