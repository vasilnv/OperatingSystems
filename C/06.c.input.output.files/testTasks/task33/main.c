#include <err.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>

int cmp(const void* a, const void* b)
{
//	return *((unsigned char*) a) - *((unsigned char*)b);
	if ( *((uint32_t*) a)> *((uint32_t*) b) )
	{
		return 1;
	} 
	else if ( *((uint32_t*) a) < *((uint32_t*) b) ) 
	{
		return -1;
	}
	return 0;

}

int main()
{	
	struct stat st;
	if (stat("f1", &st) < 0)
	{
		err(2, "error in stat");
	}
	
	if((st.st_size % sizeof(uint32_t)) != 0)
	{
		err(3, "wrong size of f1");	
	}
	
	uint32_t numel = st.st_size / sizeof(uint32_t);
	printf("%d\n", numel);	
	
	uint32_t half = numel/2;
	uint32_t *p = malloc(half*sizeof(uint32_t));
	
	if(!p)
	{
		err(4, "failed malloc");
	
	}
	
	int fd1;
	fd1 = open("f1", O_RDONLY);
    if ( fd1 < 0 )
    {   
		free(p);
        err(1, "file failed to open");
    }

	int t1 = open("temp1", O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if (t1 < 0)
	{
		free(p);
		int olderrno = errno;
		close(fd1);
		errno = olderrno;
		err(5, "file temp1 failed to open");
	}

	printf("%ld\n", sizeof(p));	
	if ((read(fd1, p, half * sizeof(uint32_t))) != (ssize_t) (half * sizeof(uint32_t)))
	{
        free(p);
        int olderrno = errno;
        close(fd1);
		close(t1);
	    errno = olderrno;
		err(6, "error while reading from file f1");
	}
	
	qsort(p, half, sizeof(uint32_t), cmp);

	if (write(t1, p, half*sizeof(uint32_t)) != (ssize_t)(half*sizeof(uint32_t)))
	{
		int olderrno = errno;
		free(p);
		close(fd1);
		close(t1);
		errno = olderrno;
		err(7, "error while writing in file temp1");
	}
	
//	close(t1);
	free(p);

	uint32_t rhalf = numel - half;
	
	uint32_t * rp = malloc (rhalf * sizeof(uint32_t));
	if (!rp)
	{
		int olderrno = errno;
		close(fd1);
		errno=olderrno;
		err(8, "failed malloc");
	}
	
	int t2 = open ("temp2", O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
    if (t2 < 0)
    {
        free(rp);
        int olderrno = errno;
        close(fd1);
        errno = olderrno;
        err(9, "file temp2 failed to open");
    }

	if (read(fd1, rp, rhalf * sizeof(uint32_t)) != (ssize_t)(rhalf * sizeof(uint32_t)))
	{
		int olderrno=errno;
		free(rp);
		close(fd1);
		close(t2);
		errno=olderrno;
		err(10, "file f1 failed to read");
	}

	qsort (rp, rhalf, sizeof(uint32_t), cmp);
	
	if (write(t2, rp, rhalf*sizeof(uint32_t)) != (ssize_t)(rhalf * sizeof(uint32_t)))
	{
		int olderrno=errno;
        free(rp);
        close(fd1);
        close(t2);
        errno=olderrno;
        err(11, "file t2 failed to write");
	}
//	close(t2);

	free(rp);
	close(fd1);

	lseek(t1, 0, SEEK_SET);
	lseek(t2, 0, SEEK_SET);
	
	int fd2 = open("f2", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd2 < 0)
	{
		int olderrno = errno;
		close(t1);
		close(t2);
		errno = olderrno;
		err(12, "failed to open file f2");
	}
	
	uint32_t num1;
	uint32_t num2;
	
	while(read(t1, &num1, sizeof(num1)) == sizeof(num1) && read(t2, &num2, sizeof(num2)) == sizeof (num2))
	{
		if (num1 <= num2)
		{
			write(fd2, &num1, sizeof(num1));
			lseek(t2, -1*sizeof(num2), SEEK_CUR);
		}
		else 
		{
			write(fd2, &num2, sizeof(num2));
			lseek(t1, -1*sizeof(num1), SEEK_CUR);
		}
	}

	while (read (t1, &num1, sizeof(num1)) == sizeof(num1))
	{
		write(fd2, &num1, sizeof(num1));
	}
	while (read (t2, &num2, sizeof(num2)) == sizeof(num2))
	{
		write(fd2, &num2, sizeof(num2));
	}
	
	
	close(t1);
	close(t2);
	close(fd2);
	exit(0);
}

/*
	f1- input file
	f2 = output file
	t1, t2 - temp files
	
	filesize(f1) % sizeof(uint32_t) == 0;
	100 000 00 * uint32_t ~ 380 MB
	50M uint32_t * uint32_t ~ 190 MB < limit 256 MB

	numel = filesize(f1) / sizeof(uint32_t)

	read numel/2 elements from f1 in RAM
	qsort
	dump in t1
	
	read rest form f1 in RAM
	qsort
	dump in t2

	close(f1)
	
	merge sort the temp files
		
	a[], b[] ---> merge in c[] 
	both have n elements
	
	i = 0
	j = 0
	k = 0
	while (i < n && j < n)
	{
		if a[i] < b[j]
			c[k] = a[i]
			i ++
			k++
	 	else c[k] = b[j]
			j++
			k++
	}	
	while (i < n)
	{
		c[k] = a[i]
		k++; i++;
	}
	while (j < n)
	{
		c[k] = b[j]
		k++; j++;
	}
*/


