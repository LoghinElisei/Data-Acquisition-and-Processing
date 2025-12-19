//==============================================================================
//
// Title:       AiMultiChannel
// Purpose:     A short description of the application.
//
// Created on:  24-Nov-2019 at 13:52:40 by Admin.
// Copyright:   . All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include "daqmxioctrl.h"
#include <ansi_c.h>
#include <cvirte.h>     
#include <userint.h>
#include "AiDSP2.h"
#include "toolbox.h"
#include <NIDAQmx.h>
#include "analysis.h"
//==============================================================================
// Constants
#define DISPLAY_TYPE_GRAPH
//#define DISPLAY_TYPE_STRIPCHART

//==============================================================================
// Types

//==============================================================================
// Static global variables
int quitFlag = 1;
static int panelHandle;
int colors[]={VAL_BLUE,VAL_RED};

//==============================================================================
// Static functions
int32 CVICALLBACK EveryNSamples (TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
int32 CVICALLBACK DoneCallback (TaskHandle taskHandle, int32 status, void *callbackData);


// Global variables
	//freqventa de achizitie
double samplingRate = 0;
	//handle la taskul de achizitie
	//constanta ce defineste/contine amplitudinea semnalului zgomot
double noiseAmplitude1 = 1.0;
double noiseAmplitude2 = 1.0;
	//numarul de canale pe care se face achizitia semnalului
int noChannels = 0;
	//flag-uri privind prezenta sau nu a unor componente in semnalul final construit
int flagNoise1 = 0;
int flagNoise2 = 0;

	//vector ce contine semnalele achizitionate
double *acquiredSignal = 0;

//==============================================================================
// Global variables
TaskHandle taskHandle = 0;
//==============================================================================
// Global functions

/// HIFN The main entry-point function.
int main (int argc, char *argv[])
{
    int error = 0;
    
    /* initialize and load resources */
    nullChk (InitCVIRTE (0, argv, 0));
    errChk (panelHandle = LoadPanel (0, "AiDSP2.uir", MAIN_PANEL));
	
		//creare canal analogic de intrare cu multiselectie
	NIDAQmx_NewPhysChanAICtrl( panelHandle, MAIN_PANEL_IDC_CHANNEL, 1 );
	
    /* display the panel and run the user interface */
    errChk (DisplayPanel (panelHandle));
    errChk (RunUserInterface ());
	while(!quitFlag);
Error:
    /* clean up */
    DiscardPanel (panelHandle);
    return 0;
}

//==============================================================================
// UI callback function prototypes

/// HIFN Exit when the user dismisses the panel.
int CVICALLBACK OnMainPanelCB (int panel, int event, void *callbackData,
		int eventData1, int eventData2)
{
	int val = 0;
	if (event == EVENT_CLOSE)
	{
			//citesc starea butonului start task
		GetCtrlVal(panel, MAIN_PANEL_IDC_START_TASK, &val);
		if(val)
		{
				//ridic butonul
			SetCtrlVal(panel, MAIN_PANEL_IDC_START_TASK, 0);
				//apelez functia de callback a butonului start task in pozie ridicata
			OnStartTaskCB (panel, MAIN_PANEL_IDC_START_TASK, EVENT_COMMIT, 0, 0, 0);
		}
		QuitUserInterface (0);
	}
	return 0;
}



int CVICALLBACK OnStartTaskCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	double cMin = -10;
	double cMax = 10;
	char channelRange[128] = { 0 };
	/*char strTmp[64]={0};*/
	int samplesPerChannel = 0;	
	double freq = 0.0;
	double rate = 0.0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal( panel, control, &val );
			if( val )
			{
					//citire min, max, canale,esantioane per canal, frecventa de achizitie
				GetCtrlVal( panel, MAIN_PANEL_IDC_RATE, &rate );
				GetCtrlVal(panel,MAIN_PANEL_IDC_CHANNEL,channelRange);
				GetCtrlVal(panel,MAIN_PANEL_IDC_NSAMPLES,&samplesPerChannel);
				GetCtrlVal(panel,MAIN_PANEL_IDC_RATE,&freq);
					//creare task
				DAQmxCreateTask("",&taskHandle);	
					//configurare canal analogic de intrare
				DAQmxCreateAIVoltageChan(taskHandle,channelRange,"",DAQmx_Val_RSE,cMin,cMax,DAQmx_Val_Volts,NULL);
					//stabilirea mod de esantionare
				DAQmxCfgSampClkTiming(taskHandle,"",rate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,samplesPerChannel);
					//inregistrare functie de callback
				DAQmxRegisterEveryNSamplesEvent(taskHandle,DAQmx_Val_Acquired_Into_Buffer,samplesPerChannel,0,EveryNSamples,NULL);
					//inregistrare functie DoneCallback
				DAQmxRegisterDoneEvent(taskHandle,0,DoneCallback,NULL);
					//determinare numar de canale de achizitie
				DAQmxGetTaskAttribute(taskHandle,DAQmx_Task_NumChans,&noChannels);
					//pornire task
				DAQmxStartTask(taskHandle);	
			}
			else
			{
					//stop task
				DAQmxStopTask(taskHandle);
					//clear task
				DAQmxClearTask(taskHandle);
			}
			break;
	}
	return 0;
}

int32 CVICALLBACK EveryNSamples (TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData)
{
	int numRead = 0;
	unsigned int i = 0;
	double *buffer = (double*)malloc(nSamples*noChannels*sizeof(double));
	double *V1 = (double*)malloc(nSamples*sizeof(double));
	double *V2 = (double*)malloc(nSamples*sizeof(double));
	double *outCorrelate = (double *)malloc( (nSamples*2-1) * sizeof(double));
	double *outConvolve = (double *)malloc( (nSamples*2-1) * sizeof(double));
	DAQmxReadAnalogF64(taskHandle,nSamples,-1,DAQmx_Val_GroupByChannel,buffer,noChannels*nSamples,&numRead,NULL);

	DeleteGraphPlot(panelHandle,MAIN_PANEL_IDC_CHK_SIGNAL_NOISE1,-1,VAL_IMMEDIATE_DRAW);	
	DeleteGraphPlot(panelHandle,MAIN_PANEL_IDC_CHK_SIGNAL_NOISE2,-1,VAL_IMMEDIATE_DRAW);	
	DeleteGraphPlot(panelHandle,MAIN_PANEL_IDC_CORRELATE_SIGNAL,-1,VAL_IMMEDIATE_DRAW);	
	DeleteGraphPlot(panelHandle,MAIN_PANEL_IDC_CONVOLVE_SIGNAL,-1,VAL_IMMEDIATE_DRAW);	
	
	memcpy(V1,buffer,nSamples*sizeof(double));
	if ( noChannels > 1)
	{
		memcpy(V2,buffer+nSamples,nSamples * sizeof(double));
		PlotY(panelHandle,MAIN_PANEL_IDC_CHK_SIGNAL_NOISE1,buffer,nSamples,VAL_DOUBLE,VAL_THIN_LINE,VAL_EMPTY_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,colors[0]); 	
		PlotY(panelHandle,MAIN_PANEL_IDC_CHK_SIGNAL_NOISE2,buffer + nSamples,nSamples,VAL_DOUBLE,VAL_THIN_LINE,VAL_EMPTY_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,colors[0]);
	    
		Correlate(V1,nSamples,V2,nSamples,outCorrelate);
		PlotY(panelHandle,MAIN_PANEL_IDC_CORRELATE_SIGNAL,outCorrelate,nSamples*2-1,VAL_DOUBLE,VAL_THIN_LINE,VAL_EMPTY_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,colors[1]);
		PlotY(panelHandle,MAIN_PANEL_IDC_CONVOLVE_SIGNAL,outConvolve,nSamples*2-1,VAL_DOUBLE,VAL_THIN_LINE,VAL_EMPTY_SQUARE,VAL_SOLID,VAL_CONNECTED_POINTS,colors[1]);
	}
	
	
	

	
	
	
	memset(V1,0,nSamples*sizeof(double));
	memset(V2,0,nSamples*sizeof(double));
	memset(outCorrelate,0,(nSamples*2-1)*sizeof(double));
	memset(outConvolve,0,(nSamples*2-1)*sizeof(double));
	free(V1);
	free(V2);
	free(outCorrelate);
	free(outConvolve);
	
	return 0;
}



int CVICALLBACK SettingRawSignalCB (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch(control)
			{
				case MAIN_PANEL_IDC_CHK_SIGNAL_NOISE1:
					GetCtrlVal(panel, control, &flagNoise1);
					break;
				case MAIN_PANEL_IDC_CHK_SIGNAL_NOISE2:
					GetCtrlVal(panel, control, &flagNoise2);
					break;
			}
			break;
	}
	return 0;
}


int CVICALLBACK OnNoiseAmplitudeChangeCB (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch(control)
			{
				case MAIN_PANEL_IDC_NOISE_AMPLITUDE_1:
					GetCtrlVal( panel, control, &noiseAmplitude1);
					break;
				case MAIN_PANEL_IDC_NOISE_AMPLITUDE_2:
					GetCtrlVal( panel, control, &noiseAmplitude2);
					break;
			}
			break;
	}
	return 0;
}



int32 CVICALLBACK DoneCallback (TaskHandle taskHandle, int32 status, void *callbackData)
{
	MessagePopup("EXIT","Task finished");
	return 0;
}

