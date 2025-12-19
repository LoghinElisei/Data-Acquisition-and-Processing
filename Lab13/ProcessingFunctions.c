//==============================================================================
//
// Title:		ProcessingFunctions.c
// Purpose:		A short description of the implementation.
//
// Created on:	11/24/2024 at 11:50:08 AM by Terran.
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
	for(int i = 0;i < numberOfElements; i++)
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
	for (int i = 1; i < numberOfElements; i++)
	{
		outputArray[i] = (1 - alpha) * outputArray[i - 1] + alpha * inputArray[i];
	}
	return 0;
}

/********************************************************************************
	aplica moving average filter semnalului inputArray 
********************************************************************************/
int FilterMovingAverage(double inputArray[], unsigned int numberOfElements, unsigned int filterNumberOfElements, double outputArray[])
{
	double sumWnd = 0.0;

	outputArray[0] = inputArray[0];
	sumWnd = inputArray[0];
	for(int i = 1; i < filterNumberOfElements; i++)
	{
		sumWnd = sumWnd + inputArray[i];
		outputArray[i] = sumWnd / (i + 1);
	}

	for(int i = filterNumberOfElements; i < numberOfElements; i++)
	{
		sumWnd = sumWnd - inputArray[i - filterNumberOfElements] + inputArray[i];
		outputArray[i] = sumWnd / filterNumberOfElements;
	}
	return 0;
}

/********************************************************************************
	calculeaza spectrul de putere apeland functii CVI
********************************************************************************/
int ComputePowerSpectrum(double inputArray[], unsigned int numberOfElements, double samplingRate, double convertedSpectrum[], double *frequencyInterval, double *powerPeak, double *freqPeak)
{
		//voltage signal - descriere a semnalului achizitionat
	char unit[32] = "V";
		//spectrul de putere cu un numar de valori egal cu jumatate din dimensiunea bufferuluide intrare
	double autoSpectrum[numberOfElements/2];
		//
	WindowConst winConst;
	
		//aplatizare forma semnal la capetele intervalului
	ScaledWindow (inputArray, numberOfElements, RECTANGLE_, &winConst);
		//partea pozitiva a spectrului scalat de putere pentru un semnal esantionat
	AutoPowerSpectrum (inputArray, numberOfElements, 1.0/samplingRate, autoSpectrum, frequencyInterval);
		//calculeaza puterea si frecventa corespunzatoare varfului din spectrul semnalului  
    PowerFrequencyEstimate (autoSpectrum, numberOfElements/2, -1.0, winConst, *frequencyInterval, 7, freqPeak, powerPeak);
    	//Functia converteste spectrul de intrare (care este puterea, amplitudinea sau amplificarea) 
		//în formate alternative (linear, logarithmic, dB) ce permit o reprezentare grafica mai convenabila.
    SpectrumUnitConversion (autoSpectrum, numberOfElements/2, SPECTRUM_POWER, SCALING_MODE_LINEAR, DISPLAY_UNIT_VRMS, *frequencyInterval, winConst, convertedSpectrum, unit);
	return 0;
}

/********************************************************************************
	END ProcessingFunctions.c 
********************************************************************************/