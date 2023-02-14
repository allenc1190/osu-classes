#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>
#define _USE_MATH_DEFINES

// The main Program

#define XMIN     -1.
#define XMAX      1.
#define YMIN     -1.
#define YMAX      1.

//num threads
#ifndef NUMT
    #define NUMT		8
#endif

//num nodes
#ifndef NUMNODES
    #define NUMNODES	5000
#endif

// The code to evaluate the height at a given <i>iu</i> and <i>iv</i> is:

const float N = 2.5f;
const float R = 1.2f;

 //. . .

float
Height( int iu, int iv )	// iu,iv = 0 .. NUMNODES-1
{
	float x = -1.  +  2.*(float)iu /(float)(NUMNODES-1);	// -1. to +1.
	float y = -1.  +  2.*(float)iv /(float)(NUMNODES-1);	// -1. to +1.

	float xn = pow( fabs(x), (double)N );
	float yn = pow( fabs(y), (double)N );
	float rn = pow( fabs(R), (double)N );
	float r = rn - xn - yn;
	if( r <= 0. )
	        return 0.;
	float height = pow( r, 1./(double)N );
	return height;
}

// call this if you want to force your program to use
// a different random number sequence every time you run it:
void
TimeOfDaySeed( )
{
	struct tm y2k = { 0 };
	y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
	y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

	time_t  timer;
	time( &timer );
	double seconds = difftime( timer, mktime(&y2k) );
	unsigned int seed = (unsigned int)( 1000.*seconds );    // milliseconds
	srand( seed );
}

int main( int argc, char *argv[ ] )
{

#ifndef _OPENMP
    fprintf(stderr, "No OpenMP suuport!\n");
    return 1;
#endif

	//. . .

	// the area of a single full-sized tile:
	// (not all tiles are full-sized, though)

	float fullTileArea = (  ( ( XMAX - XMIN )/(float)(NUMNODES-1) )  *
				( ( YMAX - YMIN )/(float)(NUMNODES-1) )  );

	// sum up the weighted heights into the variable "volume"
	// using an OpenMP for-loop and a reduction:

	//?????

    omp_set_num_threads(NUMT);
	double volume = 0.0;
	double time0 = omp_get_wtime();

	// You could use a single for-loop over all the nodes that looks like this:
	#pragma omp parallel for default(none), shared(fullTileArea), reduction(+:volume)
	for( int i = 0; i < NUMNODES*NUMNODES; i++ )
	{
		int iu = i % NUMNODES;
		int iv = i / NUMNODES;
		float z = Height(iu, iv);

		//if edge tile. 1/2 area
		if((iu == 0) || (iu == NUMNODES-1) || (iv==0) || (iv == NUMNODES-1)){
			volume += ((fullTileArea/2) * Height(iu, iv));
		}

		//if corner tile. 1/4 area
		else if(((iu == 0) || (iu == NUMNODES-1)) && ((iv==0) || (iv == NUMNODES-1))){
			volume += ((fullTileArea/4) * Height(iu, iv));
		}

		volume += 2*(fullTileArea * Height(iu, iv));
	}

	double time1 = omp_get_wtime();
	double megaHeightsPerSec = ((double)NUMNODES*(double)NUMNODES)/(time1-time0)/1000000;

    fprintf(stderr, "%d threads : %d nodes : volume = %lf ; megaHeight/sec = %lf\n", NUMT, NUMNODES, volume, megaHeightsPerSec);

	fprintf(stdout, "%d, %d, %lf, %lf\n", NUMT, NUMNODES, volume, megaHeightsPerSec);

    return 0;
}