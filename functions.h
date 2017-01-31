#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "tinydir.h"

typedef struct parallaldos{
	int height;
	int width;
	char ** pixels;
	char * filename;
}parallaldo;

typedef struct return_index{
	int y;
	int x;
	int r;
}Index;

typedef struct array{
	int i;
	struct parallaldos *alldos;
}parray;

/*
getParallaldo:
Purpose:retrieves the parallaldo from the given file
Parameteres:FILE *, char *
Returns:parallado
Memory:memory allocated for parallaldo.pixels, parallaldo.pixels[i] and parallaldo.filename
*/
parallaldo getParallaldo(FILE * file, char *filename);

/*
searchImage:
Purpose:iterates through an image and passes each point to checkLocation to determine if a parallaldo is found
Parameteres:parallaldo, parallaldo, rotation, width, height
Returns:int
Memory:no memory allocated
*/
int searchImage(parallaldo i, parallaldo p, int rotation, int width, int height);

/*
checkLocation:
Purpose:from a given point in an image checks if the following points match a parallaldo
Parameteres:int, int, int, parallaldo, parallaldo
Returns:int
Memory:no memory allocated
*/
int checkLocation(int x_start, int y_start, int rotation, parallaldo i, parallaldo p);

/*
destroyParallaldos:
Purpose:frees any memory malloced for the parallaldo structures
Parameteres:parallaldo
Returns:nothing
Memory:no memory allocated
*/
void destroyParallaldos(parallaldo p);

/*
createArray:
Purpose:Generates an array of structures from a given file
Parameteres:char *
Returns:parray
Memory:array.alldos malloced and must be freed in calling function
*/
parray createArray(char * path);

/*
destroyArray:
Purpose:frees any memory allocated to the creation of arrays
Parameteres:parray, int
Returns:nothing
Memory:no memory allocated
*/
void destroyArray(parray array, int i);

/*
parallel:
Purpose:Runs the program in parallel mode
Parameteres:parray, int, char
Returns:nothing
Memory:no memory allocated
*/
void parallel(parray array, int N, char *tpath);

/*
serial:
Purpose: Runs the program in serial mode
Parameteres:parray, int, char
Returns:nothing
Memory:No memory allocated
*/
void serial(parray array, int i, char *tpath);

/*
printParallaldos:
Purpose:
Parameteres:
Returns:
Memory:
*/
void printParallaldos(parray array, int k);