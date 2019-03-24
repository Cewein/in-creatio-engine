#pragma warning(disable : 4996)
#include "utils.h"

long fsize(FILE * fp)
{
	long bytes;
	fseek(fp, 0, SEEK_END);
	bytes = ftell(fp);
	rewind(fp);
	//printf("%ld", bytes);
	return bytes;
}

//return a file into a char *
char * freadInArray(FILE * fp)
{ 

	char * buffer = (char*)malloc(sizeof(char) * 250);
	char * fileArray = (char*)calloc(1, fsize(fp) + 1); //we calloc because we need a empty array (or at least filled with 0)

	while (fgets(buffer, 250, fp) != NULL)
	{
		strcat(fileArray, buffer);
	}

	free(buffer);

	return fileArray;
}