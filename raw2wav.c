#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef _MSC_VER
#include <unistd.h>
#else
#include <msvc_missing/libc/optarg.h>
#endif
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include "wav.h"
#define BUF_SIZE    8192
int main(int argc, char *argv[])
{
	struct WAVHEADER_t header;
	struct stat fs;
	int in_fd, out_fd, actlen, rate, nchans, fmt, aopt;
	char buf[BUF_SIZE];

	if (argc < 3) {
		printf("command: %s rawfile wavfile [-rxx] [-fxx] [-cxx]\n",
		    argv[0]);
		return (EXIT_FAILURE);
	}
	#if 0
	rate = 8000;
	nchans = 1;
	fmt = 8;
	#else
	rate = 16000;
	nchans = 1;
	fmt = 16;
	#endif
	if (stat(argv[1], &fs) == -1) {
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	if ((in_fd = open(argv[1], O_RDONLY | O_BINARY)) == -1) {
		perror(argv[1]);
		return (EXIT_FAILURE);
	}
	if ((out_fd = open(argv[2], O_WRONLY|O_CREAT | O_BINARY, 0777)) == -1) {
		perror(argv[2]);
		return (EXIT_FAILURE);
	}
	while ((aopt = getopt(argc, argv, "r:f:c")) != -1)
		switch (aopt)
		{
		case 'r':
			if (optarg != NULL) rate = atoi(optarg);
			break;

		case 'f':
			if (optarg != NULL) fmt = atoi(optarg);
			break;

		case 'c':
			if (optarg != NULL) nchans = atoi(optarg);
			break;
		}

	fillheader(&header, nchans, rate, fmt, fs.st_size);
	write(out_fd, &header, sizeof(header));
	while ((actlen = read(in_fd, buf, BUF_SIZE)) > 0)
		write(out_fd, buf, actlen);
	close(out_fd);
	close(in_fd);
}
