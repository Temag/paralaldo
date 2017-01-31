/*
Name: Braydon Johnson
ID: 0785445
File: createArray.c
Purpose: Contains my function to generate parllaldo arrays, takes a directory
path and loads the parallaldo/image from each file into an array
*/

#include "functions.h"
parray createArray(char * dirpath)
{
	int i=0, j, size, sub=0, offset;
	char path[100];
	FILE * pfile;
	parray array;
	tinydir_dir dir;
    tinydir_file file;
    tinydir_open_sorted(&dir, dirpath);
	size = (int)dir.n_files;

  array.alldos = malloc(sizeof(parallaldo)*(size));

	#pragma omp parallel for private(file, path) schedule(dynamic)
    for(j=0; j<(int)dir.n_files; j++)
    {
        tinydir_readfile_n(&dir, &file, j);

        /*
        Create pathway to open file
        */
        strcpy(path, dir.path);
        strcat(path, "/");
        strcat(path, file.name);
        path[strlen(path)] = '\0';

        /*
        Removes addition files within directory that shouldn't be opened
        */
        if((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0) && strcmp(file.name, ".DS_Store") != 0)
        {
           if((pfile = fopen(path, "r")) != NULL)
            {
                array.alldos[j-2] = getParallaldo(pfile, file.name);
                fclose(pfile);
            }

            else
            {
                fprintf(stderr, "Error opening file\n");
                exit(0);
            }
            i++;

        }
		else
		{
			sub++;
		}
	}
    tinydir_close(&dir);
    array.i = size-2;
    return array;
}
