#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <err.h>
int cmp(const void* a, const void* b)
{
//	return *((unsigned char*) a) - *((unsigned char*)b);

	if (*((uint32_t*)a) <  *((uint32_t*)b))
	{
		return -1; 
	}
	else if (*((uint32_t*) a) > *((uint32_t*)b))
	{
		return 1;
	}
	return 0;

}


int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		errx(1, "wrong number of parameters");
	}

	int f1 = open(argv[1], O_RDONLY);
	int t1 = open("t1", O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	
	struct stat st;
	if (stat(argv[1], &st))
	{
		err(2, "failed to stat");
	} 
	
	uint32_t nels = st.st_size / sizeof(uint32_t);	
	uint32_t half = nels / 2;
	uint32_t* p = malloc(half * sizeof(uint32_t));
	
	read(f1, p, half * sizeof(uint32_t));

	qsort(p, half, sizeof(uint32_t), cmp);
	
	write (t1, p, half * sizeof(uint32_t));
	
	half = nels - half;
	
	int t2 = open("t2", O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR);
	
	p = malloc (half * sizeof(uint32_t));
	
    read(f1, p, half * sizeof(uint32_t));

    qsort(p, half, sizeof(uint32_t), cmp);

    write (t2, p, half * sizeof(uint32_t));

	int f2 = open(argv[2], O_CREAT | O_RDWR | O_TRUNC , S_IRUSR | S_IWUSR);

	uint32_t curr1;
	uint32_t curr2;
	lseek(t1, 0, SEEK_SET);
	lseek(t2, 0, SEEK_SET);
	while(read(t1, &curr1, sizeof(uint32_t)) && read(t2, &curr2, sizeof(uint32_t)))
	{
		if(curr1 <= curr2)
		{
			write(f2, &curr1, sizeof(uint32_t));
			lseek(t2, -1 * sizeof(uint32_t), SEEK_CUR);
		}
		else 
		{
            write(f2, &curr2, sizeof(uint32_t));
            lseek(t1, -1 * sizeof(uint32_t), SEEK_CUR);
		}		
	}

	while(read(t1, &curr1, sizeof(uint32_t)))
	{
		write(f2, &curr1, sizeof(uint32_t));
	}

	while(read(t2, &curr2, sizeof(uint32_t)))
	{
		write(f2, &curr2, sizeof(uint32_t));
	}

	free(p);
	close(t2);
	close(f1);
	close(t1);
	exit(0);
}



/*
pseudocode

input
	input.bin

output
	output.bin

struct stat st
stat(input)

half = st.st_size/2;

uint32_t* p = malloc(half*sizeof(uint32_t));
read from f1 with size half*sizeof(uint32_t) in p

qsort(p)

same for other half

merge sort for the two temp files 

*/
