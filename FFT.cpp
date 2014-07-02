// FFT.cpp: implementation of the CFFT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <math.h>

#include "Accordage Guitare.h"
#include "FFT.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#define  DDC_PI  (3.14159265358979323846)
#define CHECKPOINTER(p)  CheckPointer(p,#p)
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFFT::CFFT()
{

}

CFFT::~CFFT()
{

}

void CFFT::fft_float(unsigned int NumSamples, int InverseTransform, float *RealIn, float *ImagIn,float *RealOut, float *ImagOut )
{

	unsigned NumBits; /* nombre de bits nécessaire pour stocker les indices */
	unsigned i, j, k, n;
	unsigned BlockSize, BlockEnd;
	double angle_numerator = 2.0 * DDC_PI;
	double tr, ti;  /* temp reel, temp imaginaire */

	if ( !IsPowerOfTwo(NumSamples) )
	{
		fprintf (stderr,"Erreur dans fft():  NumSamples=%u n'est pas une puissance de deux\n",NumSamples );
		exit(1);
	}
	if ( InverseTransform )
		angle_numerator = -angle_numerator;

	CHECKPOINTER ( RealIn );
	CHECKPOINTER ( RealOut );
	CHECKPOINTER ( ImagOut );
	NumBits = NumberOfBitsNeeded ( NumSamples );
 /*
 **   Fait des copies de données et du tri, pour les valeurs en sortie, en simultané
 */
	for ( i=0; i < NumSamples; i++ )
	{
		j = ReverseBits ( i, NumBits );
		RealOut[j] = RealIn[i];
		ImagOut[j] = (ImagIn == NULL) ? 0.0 : ImagIn[i];
	}
 /*
 **   La FFT elle-même
 */
	BlockEnd = 1;
	for ( BlockSize = 2; BlockSize <= NumSamples; BlockSize <<= 1 )
	{
		double delta_angle = angle_numerator / (double)BlockSize;
		double sm2 = sin ( -2 * delta_angle );
		double sm1 = sin ( -delta_angle );
		double cm2 = cos ( -2 * delta_angle );
		double cm1 = cos ( -delta_angle );
		double w = 2 * cm1;
		double ar[3], ai[3];
		double temp;
		for ( i=0; i < NumSamples; i += BlockSize )
		{
			ar[2] = cm2;
			ar[1] = cm1;
			ai[2] = sm2;
			ai[1] = sm1;
			for ( j=i, n=0; n < BlockEnd; j++, n++ )
			{
				ar[0] = w*ar[1] - ar[2];
				ar[2] = ar[1];
				ar[1] = ar[0];
				ai[0] = w*ai[1] - ai[2];
				ai[2] = ai[1];
				ai[1] = ai[0];
				k = j + BlockEnd;
				tr = ar[0]*RealOut[k] - ai[0]*ImagOut[k];
				ti = ar[0]*ImagOut[k] + ai[0]*RealOut[k];
				RealOut[k] = RealOut[j] - tr;
				ImagOut[k] = ImagOut[j] - ti;
				RealOut[j] += tr;
				ImagOut[j] += ti;
			}
		}
		BlockEnd = BlockSize;
	}
 /*
 **   Il faut normaliser si on fait une transformation inverse
 */
	if ( InverseTransform )
	{
		double denom = (double)NumSamples;
		for ( i=0; i < NumSamples; i++ )
		{
			RealOut[i] /= denom;
			ImagOut[i] /= denom;
		}
	}
}

int CFFT::IsPowerOfTwo(unsigned int x)
{
	if ( x < 2 )
		return FALSE;
	if ( x & (x-1) )  
		return FALSE;
 
	return TRUE;


}

void CFFT::CheckPointer(void *p, char *name)
{
	if ( p == NULL )
	{
		fprintf ( stderr, "Erreur dans fft_float():  %s == NULL\n", name );
		exit(1);
	}
}

unsigned CFFT::NumberOfBitsNeeded(unsigned int PowerOfTwo)
{
	unsigned i;
	if ( PowerOfTwo < 2 )
	{
		fprintf (stderr,">>> Erreur dans fftmisc.c: argument %d de NumberOfBitsNeeded est trop petit.\n",PowerOfTwo );
		exit(1);
	}
	for ( i=0; ; i++ )
	{
		if ( PowerOfTwo & (1 << i) )
			return i;
	}
}

unsigned CFFT::ReverseBits(unsigned int index, unsigned int NumBits)
{
	unsigned i, rev;

	for ( i=rev=0; i < NumBits; i++ )
	{
		rev = (rev << 1) | (index & 1);
		index >>= 1;
	}

	return rev;
}
