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
#include "AiMultiChannel.h"
#include "toolbox.h"
#include <NIDAQmx.h>

//==============================================================================
// Constants
//#define DISPLAY_TYPE_GRAPH
#define DISPLAY_TYPE_STRIPCHART

//==============================================================================
// Types

//==============================================================================
// Static global variables
int quitFlag = 1;
static int panelHandle;
int noChannels = 0;
int colors[]={VAL_BLUE,VAL_RED};

//==============================================================================
// Static functions
int32 CVICALLBACK EveryNSamples (TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData);
int32 CVICALLBACK DoneCallback (TaskHandle taskHandle, int32 status, void *callbackData);

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
    errChk (panelHandle = LoadPanel (0, "AiMultiChannel.uir", MAIN_PANEL));
	
		//creare canal analogic de intrare cu multiselectie
	NIDAQmx_NewPhysChanAICtrl( panelHandle, MAIN_PANEL_IDC_CHANNELS, 1 );
	
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
int CVICALLBACK MainPanelCB (int panel, int event, void *callbackData,
        int eventData1, int eventData2)
{
    if (event == EVENT_CLOSE)
        QuitUserInterface (0);
    return 0;
}


int CVICALLBACK OnStartAi (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	double cMin = 0;
	double cMax = 0;
	char channelRange[128] = { 0 };
	char strTmp[64]={0};
	int samplesPerChannel = 0;	
	
	double rate = 0.0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal( panel, control, &val );
			if( val )
			{
					//citire min, max, canale,esantioane per canal, frecventa de achizitie
				GetCtrlVal( panel, MAIN_PANEL_IDC_MIN, &cMin );
				GetCtrlVal( panel, MAIN_PANEL_IDC_MAX, &cMax );
				GetCtrlVal( panel, MAIN_PANEL_IDC_CHANNELS, channelRange );
				GetCtrlVal( panel, MAIN_PANEL_IDC_SAMP_PER_CHANNEL, &samplesPerChannel );
				GetCtrlVal( panel, MAIN_PANEL_IDC_RATE, &rate );
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

#ifdef DISPLAY_TYPE_STRIPCHART
		//setez numarul de puncte pe ecran pentru controlul de tip strichart
	SetCtrlAttribute( panel, MAIN_PANEL_IDC_STRIPCHART, ATTR_POINTS_PER_SCREEN, samplesPerChannel );
		//setez numarul de forme de unda pentur controlul de tip stripchart
	SetCtrlAttribute( panel, MAIN_PANEL_IDC_STRIPCHART, ATTR_NUM_TRACES, noChannels);
#endif

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
	double buffer[noChannels * nSamples];
	int numRead = 0;
	int i = 0;

	quitFlag = 0;	
	//daca folosesc graf
#ifdef DISPLAY_TYPE_GRAPH
		//citire esantioane
	DAQmxReadAnalogF64(taskHandle,nSamples,2,DAQmx_Val_GroupByChannel,buffer,noChannels*nSamples,&numRead,NULL);
		//stergerea graph-ului
	DeleteGraphPlot(panelHandle,MAIN_PANEL_IDC_GRAPH,-1,VAL_IMMEDIATE_DRAW);	
		//plotare forme de unda pe un graph
	for( i = 0; i < noChannels; i++ )
	{
		PlotY(panelHandle,MAIN_PANEL_IDC_GRAPH,buffer + i*nSamples,nSamples,VAL_DOUBLE,VAL_FAT_LINE,VAL_DOTTED_SOLID_CIRCLE,VAL_SOLID,1,colors[i]); 	
	}
#endif

	//daca folosesc stripchart
#ifdef DISPLAY_TYPE_STRIPCHART
		//citire esantioane
	DAQmxReadAnalogF64(taskHandle,nSamples,2,DAQmx_Val_GroupByScanNumber,buffer,noChannels*nSamples,&numRead,NULL);
		//plotare forme de unda pe un stripchart
	/*SetTraceAttribute(panelHandle,MAIN_PANEL_IDC_STRIPCHART, i, ATTR_TRACE_LG_VISIBLE, 1);*/
	PlotStripChart(panelHandle,MAIN_PANEL_IDC_STRIPCHART,buffer,noChannels*nSamples,0,0,VAL_DOUBLE);
#endif

	quitFlag = 1;
	return 0;
}

int32 CVICALLBACK DoneCallback (TaskHandle taskHandle, int32 status, void *callbackData)
{
	MessagePopup("EXIT","Task finished");
	return 0;
}

