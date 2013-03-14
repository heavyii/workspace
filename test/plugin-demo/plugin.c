/*
 * plugin.c
 *
 *  Created on: Mar 5, 2013
 *      Author: heavey
 */

//Load the ls.so library, and ls arg[1]

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
	void *handle;
	int (*ls)(char *path);

	if (argc != 2) {
		printf("a single argument (the directory name) is required");
		return EXIT_FAILURE;;
	}

	handle = dlopen("ls.so", RTLD_LAZY);
	if (!handle) {
		fprintf(stderr, "    # export LD_LIBRARY_PATH=/path/to/plugin/folder\n");
		fprintf(stderr, "    dlopen: %s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	dlerror(); /* Clear any existing error */

	ls = dlsym(handle, "ls");
	if (ls == NULL) {
		fprintf(stderr, "%s\n", dlerror());
		exit(EXIT_FAILURE);
	}

	ls(argv[1]);

	dlclose(handle);
	exit(EXIT_SUCCESS);
}
