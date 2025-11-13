#include "daqmxioctrl.h"
#include <NIDAQmx.h>
#include <cvirte.h>
#include <userint.h>
#include "Aquisition.h"
#include <stdlib.h>

static int mainPanel;
static _Bool buttonState = FALSE;
static TaskHandle taskHandle;
static float64 buffer[1024]={0};
static int numRead = 0;

int DAQmxErrChk(int errCode)
{
	char errBuff[2048] = {'\0'};
	if(errCode < 0)
	{
		if(DAQmxGetExtendedErrorInfo(errBuff,2047) == 0)
			MessagePopup("Error",errBuff);
	}

	return errCode;
}

static int err=0;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "Aquisition.uir", MAIN_PANEL)) < 0)
		return -1;

	err = DAQmxErrChk(NIDAQmx_NewPhysChanAICtrl(mainPanel,MAIN_PANEL_IDC_CHANNEL,1));
	DisplayPanel (mainPanel);
	RunUserInterface ();
	DiscardPanel (mainPanel);
	return 0;
}

int CVICALLBACK MainPanelCB (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:

			break;
	}
	return 0;
}

int CVICALLBACK OnRange (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			switch(control)
			{
				case MAIN_PANEL_IDC_VMIN:

					break;

				case MAIN_PANEL_IDC_VMAX:

					break;
			}
			break;
	}
	return 0;
}

int CVICALLBACK QuitCallback (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}


int32 CVICALLBACK EveryNCallback(TaskHandle taskHandle, int32 everyNsamplesEventType, uInt32 nSamples, void *callbackData)
{
	DAQmxReadAnalogF64(taskHandle,nSamples,3,DAQmx_Val_GroupByScanNumber,buffer,nSamples,&numRead,NULL);
	PlotStripChart(mainPanel,MAIN_PANEL_IDC_DISPLAY_CHART,buffer,numRead,0,0,VAL_DOUBLE);			
	
	return 0;
}

int32 CVICALLBACK DoneCallback(TaskHandle taskHandle, int32 status, void *callbackData)
{
	MessagePopup("FINISH","The currently task has finished");
	return 0;
}


int CVICALLBACK OnStartStopButton (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	char channel[1024] = "\0";
	double min,max;
	unsigned int samplesPerChannel;
	double rate;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_CHANNEL,channel);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_VMIN,&min);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_VMAX,&max);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_SAMPLES_PER_CHN,&samplesPerChannel);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_SAMPLING_RATE,&rate);



			buttonState = !buttonState;

			switch(buttonState)
			{
				case TRUE:
					err =  DAQmxErrChk(DAQmxCreateTask("",&taskHandle));
					if(err < 0)
					{
						return -1;
					}



					err =  DAQmxErrChk(DAQmxCreateAIVoltageChan(taskHandle,channel,"",DAQmx_Val_RSE,min,max,DAQmx_Val_Volts,NULL));
					if(err < 0)
					{
						return -1;
					}

					err = DAQmxErrChk(DAQmxCfgSampClkTiming(taskHandle,"",rate,DAQmx_Val_Rising,DAQmx_Val_ContSamps,samplesPerChannel));
					if(err < 0)
					{
						return -1;
					}

					err =DAQmxErrChk( DAQmxRegisterEveryNSamplesEvent(taskHandle,DAQmx_Val_Acquired_Into_Buffer,samplesPerChannel,0,EveryNCallback,NULL) );
					if(err < 0)
					{
						return -1;
					}

					DAQmxRegisterDoneEvent(taskHandle,0,DoneCallback,NULL);
					err =DAQmxErrChk(DAQmxStartTask(taskHandle));
					if(err < 0)
					{
						return -1;
					}
					
					SetAxisScalingMode(mainPanel,MAIN_PANEL_IDC_DISPLAY_CHART,VAL_LEFT_YAXIS,VAL_MANUAL,min,max);
					SetAxisScalingMode(mainPanel,MAIN_PANEL_IDC_DISPLAY_CHART,VAL_BOTTOM_XAXIS,VAL_AUTOSCALE,0,0);
					
					break;
					
				case FALSE:
					err =DAQmxErrChk(DAQmxStopTask(taskHandle));
					if(err < 0)
					{
						return -1;
					}
					err =DAQmxErrChk(DAQmxClearTask(taskHandle));
					if(err < 0)
					{
						return -1;
					}
					break;
			}

			break;
	}
	return 0;
}
