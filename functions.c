/*
Name: Braydon Johnson
ID: 0785445
File: functions.c
Purpose: This file contains all the smaller functions that setup the parallaldo/image structures,
destroy the structures, and do searches to determine whether a parallaldo is in a given structure.
*/

#include "functions.h"


parallaldo getParallaldo(FILE * file, char * filename)
{
    parallaldo new_p;
    int height, width;
    int i;
    if(filename == NULL)
    {
    	printf("Error!\n");
    	exit(0);
    }
    new_p.filename = (char*)malloc(sizeof(char)*strlen(filename));
    if(new_p.filename == NULL)
    {
        printf("Error: memory not allocated for filename.\n");
        exit(0);
    }
    fscanf(file, "%d %d ", &height, &width);
    strcpy(new_p.filename, filename);
    new_p.height = height;
    new_p.width = width;
    new_p.pixels = (char**)malloc(sizeof(char*)*(new_p.height));
    if(new_p.pixels == NULL)
    {
        printf("Error: memory not allocated for pixels.\n");
        exit(0);
    }

    for(i=0; i<new_p.height; i++)
    {
        new_p.pixels[i] =(char*) malloc(sizeof(char)*(new_p.width+1));
        if(new_p.pixels[i] == NULL)
        {
        	printf("Error: memory not allocated for pixels[i]\n");
        	exit(0);
        }
        fscanf(file, "%s", new_p.pixels[i]);
    }

    return new_p;
}

int searchImage(parallaldo i, parallaldo p, int rotation, int width, int height)
{
    int x, y;
    Index index;
    index.r = rotation;

    for(y=0; y<(i.height-(height-1)); y++)
    {
        index.y = y;
        for(x=0; x<(i.width-(width-1)); x++)
        {
            index.x = x;
            if(checkLocation(x, y, rotation, i, p))
            {
                switch(rotation)
                {
                    case 0:
                        index.y += 1;
                        index.x += 1;
                        break;
                    case 90:
                        index.y += 1;
                        index.x = index.x + p.height;
                        break;
                    case 180:
                        index.y = index.y + p.height;
                        index.x = index.x + p.width;
                        break;
                    case 270:
                        index.y = index.y + p.width;
                        index.x += 1;
                        break;
                }
                printf("%s %s (%d, %d, %d)\n", p.filename, i.filename, index.y, index.x, index.r);
                return 1;
            }
        }
    }
    return 0;
}

int checkLocation(int x, int y, int rotation, parallaldo i, parallaldo p)
{
    int x_start, y_start,x_end, y_end, y_next, x_next, y_offset, x_offset, xp, yp;
    switch(rotation)
    {
        case 0:
            x_start = 0;
            y_start = 0;
            x_end = p.width-1;
            y_end = p.height-1;
            x_next = 1;
            y_next = 1;
            break;
        case 180:
            x_start = p.width-1;
            y_start = p.height-1;
            x_end = 0;
            y_end = 0;
            x_next = -1;
            y_next = -1;
            break;
        case 90:
            x_start = 0;
            y_start = p.height-1;
            x_end = p.width-1;
            y_end = 0;
            x_next = 1;
            y_next = -1;
            break;
        case 270:
            x_start = p.width-1;
            y_start = 0;
            x_end = 0;
            y_end = p.height-1;
            x_next = -1;
            y_next = 1;
            break;
    }
    if(rotation == 0 || rotation == 180)
    {
        for(y_offset = 0, yp = y_start; yp!=y_end; yp+=y_next, y_offset++)
        {
            for(x_offset = 0, xp = x_start; xp!=x_end; xp+=x_next, x_offset++)
            {
                if(!(p.pixels[yp][xp] == i.pixels[y+y_offset][x+x_offset]))
                {
                    return 0;
                }
            }
        }
    }

    else if(rotation == 90 || rotation == 270)
    {
        for(y_offset = 0, xp = x_start; xp!=x_end; xp+=x_next, y_offset++)
        {
            for(x_offset = 0, yp = y_start; yp!=y_end; yp+=y_next, x_offset++)
            {
                if(!(p.pixels[yp][xp] == i.pixels[y+y_offset][x+x_offset]))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void destroyArray(parray array, int i)
{
    int j;
    for(j=0; j<i; j++)
    {
        destroyParallaldos(array.alldos[j]);
    }
    free(array.alldos);
}

void destroyParallaldos(parallaldo p)
{
    int j;

    for(j=0; j<p.height;j++)
    {
        free(p.pixels[j]);
    }
    free(p.filename);
    free(p.pixels);
}

void printParallaldos(parray array, int k)
{
    int i, j;

    for(i = 0; i<k; i++)
    {
        for(j=0; j<array.alldos[i].height; j++)
        {
            printf("%s\n", array.alldos[i].pixels[j]);
        }
    }
}