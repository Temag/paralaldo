/*
Name: Braydon Johnson
ID: 0785445
File: main.c
Purpose: Contains the main calling function, which calls either the serial or parallel version
of this program depending on the number of desired cores
*/

#include "functions.h"
#include "wallclock.h"
int main(int argc, char * argv[])
{
	parray array;
	int N;
	double time;
	StartTime();
	N = atoi(argv[3]);
	omp_set_num_threads(N);
    array = createArray(argv[1]);
    if(N == 1)
    {
        serial(array, array.i, argv[2]);
    }
    
    if(N>1)
    {
        parallel(array, N, argv[2]);
    }
    
    //printParallaldos(array, array.i);
    //destroyArray(array, array.i);
	time = EndTime();
	printf("Time: %.4lf\n", time);
	getchar();
    return 0;
}