//==============================================================================
//
// Title:		ProcessingFunctions.c
// Purpose:		A short description of the implementation.
//
// Created on:	11/24/2024 at 11:50:08 AM by .
// Copyright:	. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <ansi_c.h>
#include <advanlys.h>

/********************************************************************************
	functie ce copiaza inputaArray in outpoutArray
********************************************************************************/
int FilterNone(double inputArray[], unsigned int numberOfElements, double outputArray[])
{
	for(int i=0; i<numberOfElements; i++)
	{
		outputArray[i] = inputArray[i];
	}
	return 0;
}

/********************************************************************************
	filtreaza semnalul inputArray dupa formula:
	y[i] = (1 - alpha) * y[i - 1] + alpha * x[i]
********************************************************************************/
int FilterAlpha(double inputArray[], unsigned int numberOfElements, double alpha, double outputArray[])
{
	outputArray[0] = inputArray[0];
	for(int i = 1; i < numberOfElements ; i++)
	{
		outputArray[i] = (1-alpha) * outputArray[i-1] + alpha * inputArray[i];
	}
	return 0;
}

/********************************************************************************
	aplica moving average filter semnalului inputArray
********************************************************************************/
int FilterMovingAverage(double inputArray[], unsigned int numberOfElements, unsigned int filterNumberOfElements, double outputArray[])
{
	double sum=0.0;
	unsigned int N = filterNumberOfElements;
	outputArray[0] = inputArray[0];
	int st,dr;
	for(int i = 1; i < numberOfElements ; i++)
	{
		st = i-N/2;
		dr = i+N/2;
		sum = 0.0;
		if( st < 0 )
		{
			st = 0;
		}
		if(dr > (numberOfElements-1))
		{
			dr = numberOfElements - 1;
		}
		for( int j = st; j <= dr; j++)
		{
			sum = sum+inputArray[j];
		}
		outputArray[i]=(double)sum/N;
	}

	return 0;
}

/********************************************************************************
	calculeaza spectrul de putere apeland functii CVI
********************************************************************************/
int ComputePowerSpectrum(double inputArray[], unsigned int numberOfElements, double samplingRate, double convertedSpectrum[], double *frequencyInterval, double *powerPeak, double *freqPeak)
{
	WindowConst winConst;
	char unit[32]="V";
	ScaledWindowEx(inputArray,numberOfElements,RECTANGLE_,0,&winConst);

	AutoPowerSpectrum(inputArray,numberOfElements,1.0/numberOfElements,convertedSpectrum,frequencyInterval);
	double max = -1;
	for( int i = 0; i < numberOfElements, i++)
	{
		if(max > convertedSpectrum[i])
		{
			max = convertedSpectrum[i];
		}
	}


	PowerFrequencyEstimate(convertedSpectrum,numberOfElements,-1,winConst,*frequencyInterval,7.0,freqPeak,&max);

	SpectrumUnitConversion(convertedSpectrum,numberOfElements,0,SCALING_MODE_LINEAR,DISPLAY_UNIT_VRMS,*frequencyInterval,winConst,convertedSpectrum,unit);



	return 0;
}

/********************************************************************************
	calculeaza spectrul de putere conform informatiilor primite la curs
********************************************************************************/
int ComputePowerSpectrum2(double inputArray[], unsigned int numberOfElements, double samplingRate, double frequencyArray[], double ps[], double WfR[], double WfI[])
{
	double x;
	double delta_t, delta_f;
	for( int i = 0; i < numberOfElements; i++)
	{
		WfR[i] = inputArray[i];
		WfI[i] = 0;
	}

	FFT(WfR,WfI,numberOfElements);

	for( int i=0; i< numberOfElements-1; i++)
	{
		//spectrul dupa formula
		x = WfR[i] + WfR[i] + WfI[i] * WfI[i];
		ps[i] = x / pow((double) numberOfElements, 2.0);
	}

	delta_t = 1.0 / samplingRate;  //pas in timp
	delta_f = 1.0 / (numberOfElements * delta_t);  //pas in frecventa

	//construiesc axa pentru frecventa
	frequencyArray[0]=0.0;
	frequencyArray[numberOfElements-1] = 1.0 / (2*delta_t);
	
	for(int i = 0; i < numberOfElements / 2; i++)
	{
		frequencyArray[i] = i * delta_f;
		frequencyArray[numberOfElements - 1 - i] = -1 * delta_f;

	return 0;
}

/********************************************************************************
	END ProcessingFunctions.c
********************************************************************************/