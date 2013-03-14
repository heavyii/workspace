/*
 * ls.c
 *
 *  Created on: Mar 6, 2013
 *      Author: heavey
 */
 #include <sys/types.h>
 #include <dirent.h>
 #include <stdio.h>

int ls(char *path)
{
	DIR				*dp;
	struct dirent	*dirp;

	if ( (dp = opendir(path)) == NULL) {
		printf("can't open %s", path);
		return -1;
	}

	while ( (dirp = readdir(dp)) != NULL)
		printf("%s\n", dirp->d_name);

	closedir(dp);
	return 0;
}
