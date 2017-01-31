/*
Name: Braydon Johnson
ID: 0785445
File: parallel.c
Purpose: Contains all code pertinent to the parallel version of this code, void parallel()
creates and joins the created threads, void *worker() is the function each thread runs.
*/

#include "functions.h"


void parallel(parray array, int N, char *tpath)
{
    int j, k, l, rotation, width, height, check;
	parallaldo localp;
	parray globalp;
    globalp = createArray(tpath);

	#pragma omp parallel for private(j, k, l, rotation, width, height, check, localp) schedule(guided)
	for(l=0; l<globalp.i; l++)
	{
		localp=globalp.alldos[l];

		for(j=0; j<array.i; j++)
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
				if((check = searchImage(localp, array.alldos[j], rotation, width, height)))
				{
					k=4;
					j=array.i;
				}
			}
		}
	}
    //destroyArray(globalp, globalp.i);
}
