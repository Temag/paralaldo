/*
Name: Braydon Johnson
ID: 0785445
File: createArray.c
Purpose: Contains all pertinent information for the serial version of this program
*/

#include "functions.h"
void serial(parray array, int i, char * tpath)
{
    int j, k, rotation, check, width, height;
    FILE * pfile;
    char path[100];
    parallaldo image;
    tinydir_dir dir;
    tinydir_file file;
    tinydir_open(&dir, tpath);
    while(dir.has_next)
    {
        tinydir_readfile(&dir, &file);
        strcpy(path, dir.path);
        strcat(path, "/");
        strcat(path, file.name);
        if((strcmp(file.name, ".") != 0) && (strcmp(file.name, "..") != 0) && strcmp(file.name, ".DS_Store") != 0)
        {
            if((pfile = fopen(path, "r")) != NULL)
            {
                image = getParallaldo(pfile, file.name);
                fclose(pfile);
            }

            else
            {
                fprintf(stderr, "Error opening file\n");
                exit(0);
            }

            for(j=0; j<i; j++)
            {
                for(k=0; k<4; k++)
                {
                    switch(k)
                    {
                        case 0:
                            rotation = 0;
                            width = array.alldos[j].width;
                            height = array.alldos[j].height;
                            break;
                        case 2:
                            rotation = 90;
                            width = array.alldos[j].height;
                            height = array.alldos[j].width;
                            break;
                        case 1:
                            rotation = 180;
                            width = array.alldos[j].width;
                            height = array.alldos[j].height;
                            break;
                        case 3:
                            rotation = 270;
                            width = array.alldos[j].height;
                            height = array.alldos[j].width;
                            break;
                    }
                    if((check = searchImage(image, array.alldos[j], rotation, width, height)))
                    {
                        k=4;
                        j=i;
                    }
                }
            }

            destroyParallaldos(image);
            tinydir_next(&dir);
        }
        else
        {
            tinydir_next(&dir);
        }
    }
}
