//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 0.0.1
// Alexey Potehin http://www.gnuplanet.ru/doc/cv
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "base64.h"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// decode base64 to data
int do_it(const char *filename)
{
	int rc;


	rc = open(filename, O_RDONLY);
	if (rc == -1)
	{
		printf("ERROR[open()]: %s\n", strerror(errno));
		return -1;
	}
	int fd = rc;


	struct stat my_stat;
	rc = fstat(fd, &my_stat);
	if (rc == -1)
	{
		close(fd);
		printf("ERROR[fstat()]: %s\n", strerror(errno));
		return -1;
	}
	size_t size = my_stat.st_size;


	void *p_mmap = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p_mmap == MAP_FAILED)
	{
		close(fd);
		printf("ERROR[mmap()]: %s\n", strerror(errno));
		return -1;
	}


	std::string base64 = std::string((char*)p_mmap, size);
	std::string xxx = base64_decode(base64);


	rc = munmap(p_mmap, size);
	if (rc == -1)
	{
		close(fd);
		printf("ERROR[munmap()]: %s\n", strerror(errno));
		return -1;
	}


	rc = close(fd);
	if (rc == -1)
	{
		printf("ERROR[close()]: %s\n", strerror(errno));
		return -1;
	}


	for (size_t i=0; i < xxx.size(); i++)
	{
		printf("%c", xxx[i]);
	}


	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// general function
int main(int argc, char* argv[])
{
	int rc;


	if (argc != 2)
	{
		printf("example: %s file\n", argv[0]);
		return 1;
	}


	rc = do_it(argv[1]);
	if (rc == -1)
	{
		return 1;
	}


	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
