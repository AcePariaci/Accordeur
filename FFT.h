// FFT.h: interface for the CFFT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FFT_H__D151C22F_A3E0_4036_8CA0_38B13166A38B__INCLUDED_)
#define AFX_FFT_H__D151C22F_A3E0_4036_8CA0_38B13166A38B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFFT  
{
public:

	//Calcul de la fft en fonction du tableau IN, le signal passe en OUT
	void fft_float(unsigned NumSamples,int InverseTransform, float *RealIn,float *ImagIn,float *RealOut, float *ImagOut );
	CFFT();
	virtual ~CFFT();

private:
	unsigned ReverseBits(unsigned index,unsigned NumBits);	//Inversion des données
	unsigned NumberOfBitsNeeded(unsigned PowerOfTwo);	// On retrouve la puissance de 2
	static void CheckPointer(void *p,char *name);	//Vérification du pointeur
	int IsPowerOfTwo(unsigned x);	//Puissance de deux?
};

#endif // !defined(AFX_FFT_H__D151C22F_A3E0_4036_8CA0_38B13166A38B__INCLUDED_)
