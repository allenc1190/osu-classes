#include <math.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <time.h>

int	NowYear;		// 2022 - 2027
int	NowMonth;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight;		// grain height in inches
int	NowNumDeer;		// number of deer in the current population

const float GRAIN_GROWS_PER_MONTH =		15.0;
const float ONE_DEER_EATS_PER_MONTH =		1.0;

const float AVG_PRECIP_PER_MONTH =		10.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				40.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				30.0;
const float MIDPRECIP =				10.0;

unsigned int seed = 0;

int meteorHit;
int hit;

float
SQR( float x )
{
        return x*x;
}

float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}

float x = Ranf( &seed, -1.f, 1.f );

void calcTemp(){
    float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );

    float temp = AVG_TEMP - AMP_TEMP * cos( ang );
    NowTemp = temp + Ranf( &seed, -RANDOM_TEMP, RANDOM_TEMP );

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
    NowPrecip = precip + Ranf( &seed,  -RANDOM_PRECIP, RANDOM_PRECIP );
    if( NowPrecip < 0. )
        NowPrecip = 0.;
}

void Deer() {
    while(NowYear < 2028){
        int numDeer = NowNumDeer;

        if (NowNumDeer > NowHeight) {
            numDeer--;
        }
        else{
            numDeer++;
        }

    // DoneComputing barrier:
	#pragma omp barrier

    NowNumDeer = numDeer;
    

    // DoneAssigning barrier:
    #pragma omp barrier

    // DonePrinting barrier:
	#pragma omp barrier

    }
}

void Grain(){
    while(NowYear < 2028){
        float tempFactor = exp(   -SQR(  ( NowTemp - MIDTEMP ) / 10.  )   );
        float precipFactor = exp(   -SQR(  ( NowPrecip - MIDPRECIP ) / 10.  )   );
        float nextHeight = NowHeight;

        nextHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
        nextHeight -= (float)NowNumDeer * ONE_DEER_EATS_PER_MONTH;

        if(nextHeight < 0.){
            nextHeight = 0.;
        }

        #pragma omp barrier
        NowHeight = nextHeight;

        // DoneAssigning barrier:
        #pragma omp barrier
        
        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void Watcher(){
    while(NowYear < 2028){
        // DoneComputing barrier:
        #pragma omp barrier

        // DoneAssigning barrier:
        #pragma omp barrier

        //fprintf(stderr, "Month: %d, Year: %d, NumDeer: %d, Precip: %.2f, Height: %.2f, Temp: %.2f, Meteor hit: %d\n",NowMonth, NowYear, NowNumDeer, NowPrecip, NowHeight, NowTemp, hit);
        fprintf(stdout, "%d, %d, %d, %.2f, %.2f, %.2f, %d\n",NowMonth, NowYear, NowNumDeer, NowPrecip, NowHeight, NowTemp, hit);

        if(NowMonth == 11){
            NowMonth = 0;
            NowYear++;
        }
        else{
            NowMonth++;
        }

        //calculate new temp
        calcTemp();

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

void MyAgent(){
     while(NowYear < 2028){
        //rng to see if meteor hits
        meteorHit = Ranf(&seed, 0, 9);
        

        if(meteorHit == 1) {
            hit = 1;
            int kill = Ranf(&seed, 1, 2);
            for(int i = 0; i < kill; i++){
                NowNumDeer--;
            }
        }
        else{
            hit = 0;
            //rng chance of repopulating
            int repopulate = Ranf(&seed, 0, 2);

            if(repopulate == 0){
                NowNumDeer++;
            }
        }
        
        // DoneComputing barrier:
        #pragma omp barrier
        
        // DoneAssigning barrier:
        #pragma omp barrier

        
        // DonePrinting barrier:
        #pragma omp barrier

    }
}

int main (){

    // starting date and time:
    NowMonth =    0;
    NowYear  = 2022;

    // starting state (feel free to change this if you want):
    NowNumDeer = 20.;
    NowHeight =  10.;

    //calculate starting temp
    calcTemp();

    omp_set_num_threads( 4 );	// same as # of sections
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            Deer( );
        }

        #pragma omp section
        {
            Grain( );
        }

        #pragma omp section
        {
            Watcher( );
        }

        #pragma omp section
        {
            MyAgent( );	// your own
        }
    }       // implied barrier -- all functions must return in order
        // to allow any of them to get past here
}