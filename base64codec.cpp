//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// 0.0.1
// Alexey Potehin <gnuplanet@gmail.com>, http://www.gnuplanet.ru/doc/cv
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "base64.hpp"
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// global vars
namespace global
{
	bool flag_decode = true;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// decode or encode base64
int do_it(char *p, size_t size)
{
	std::string out;
	if (global::flag_decode == true)
	{
		std::string base64 = std::string(p, size);
		if (base64_decode(base64, out) == size_t(-1))
		{
			printf("ERROR[base64_decode()]: unknown error\n");
			return -1;
		}
	}
	else
	{
		if (base64_encode(p, size, out) == size_t(-1))
		{
			printf("ERROR[base64_encode()]: unknown error\n");
			return -1;
		}
	}


// view convert result
	for (size_t i=0; i < out.size(); i++)
	{
		printf("%c", out[i]);
	}


	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// read data from stdin and decode or encode base64
int do_stdinput()
{
	int rc;
	int c;


	c = getchar();
	if (c == EOF)
	{
		printf("\nERROR: stdin is close\n");
		return -1;
	}


	size_t size   = 0;
	size_t delta  = 4096;
	size_t offset = 0;


	void *p_original = NULL;
	void *p_original_old;
	char *p = (char *)p_original;


	for (;;)
	{
		if (offset >= size)
		{
			size += delta;
			p_original_old = p_original;
			p_original = realloc(p_original, size);
			if (p_original == NULL)
			{
				free(p_original_old);
				printf("ERROR[realloc()]: %s\n", strerror(errno));
				return -1;
			}
			p = (char *)p_original + offset;
			continue;
		}

		*p = c; p++; offset++;

		c = getchar();
		if (c == EOF) break;
	}


// convert data
	rc = do_it((char *)p_original, offset);
	if (rc == -1)
	{
		free(p_original);
		return -1;
	}


// free memory
	free(p_original);


	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// read file and decode or encode base64
int do_file(const char *filename)
{
	int rc;


// open file
	rc = open(filename, O_RDONLY);
	if (rc == -1)
	{
		printf("ERROR[open()]: %s\n", strerror(errno));
		return -1;
	}
	int fd = rc;


// get file size
	struct stat my_stat;
	rc = fstat(fd, &my_stat);
	if (rc == -1)
	{
		close(fd);
		printf("ERROR[fstat()]: %s\n", strerror(errno));
		return -1;
	}
	size_t size = my_stat.st_size;


// map file in memory
	void *p_mmap = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (p_mmap == MAP_FAILED)
	{
		close(fd);
		printf("ERROR[mmap()]: %s\n", strerror(errno));
		return -1;
	}


// convert data
	rc = do_it((char *)p_mmap, size);
	if (rc == -1)
	{
		munmap(p_mmap, size);
		close(fd);
		return -1;
	}


// unmap file in memory
	rc = munmap(p_mmap, size);
	if (rc == -1)
	{
		close(fd);
		printf("ERROR[munmap()]: %s\n", strerror(errno));
		return -1;
	}


// close file
	rc = close(fd);
	if (rc == -1)
	{
		printf("ERROR[close()]: %s\n", strerror(errno));
		return -1;
	}


	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// view help
void help()
{
	printf("%s    %s\n", PROG_FULL_NAME, PROG_URL);
	printf("example: %s [-d|-e] FILE [--]\n", PROG_NAME);
	printf("\n");

	printf("base64 decode and encode FILE(s), or standard input, to stdout.\n");
	printf("\n");
	printf("  -h, -help, --help                this message\n");
	printf("  -d                               decode from base64\n");
	printf("  -e                               encode to base64\n");
	printf("With no FILE, or when FILE is --, read standard input.\n");
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
// general function
int main(int argc, char *argv[])
{
	int rc;
	bool flag_file = false;


// parse command line args
	for (int i=1; i < argc; i++)
	{
		if ((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-help") == 0) || (strcmp(argv[i], "-h") == 0))
		{
			help();
			return 1;
		}
		if (strcmp(argv[i], "-d") == 0)
		{
			global::flag_decode = true;
			continue;
		}
		if (strcmp(argv[i], "-e") == 0)
		{
			global::flag_decode = false;
			continue;
		}

		if (strcmp(argv[i], "--") == 0)
		{
			break;
		}

		flag_file = true;
		rc = do_file(argv[i]);
		if (rc == -1) return 1;
	}


	if (flag_file == false)
	{
		rc = do_stdinput();
		if (rc == -1) return 1;
	}


	return 0;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
