#include "daqmxioctrl.h"
#include <cvirte.h>
#include <userint.h>
#include "AnalogOut.h"
#include "toolbox.h"
#include <NIDAQmx.h>
#include <analysis.h>


#define NUMBER_OF_POINTS 2048
typedef enum {SINUS,TRIUNGHIULAR,DREPTUNGHIULAR,TREAPTA} signalType_s;
signalType_s signalType = SINUS;
static int mainPanel;
TaskHandle taskHandle = 0;
static unsigned int nrPoints = 0;
static double buffer[NUMBER_OF_POINTS]= {0};
double amp = 0;
int err=0;
static int index = 0;
static double outVal =0 ;

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


int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "AnalogOut.uir", MAIN_PANEL)) < 0)
		return -1;

	NIDAQmx_NewPhysChanAOCtrl( mainPanel, MAIN_PANEL_IDC_CHANNEL, 1 );

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
			if(taskHandle != 0)
			{
				DAQmxStopTask(taskHandle);
				DAQmxClearTask(taskHandle);
				QuitUserInterface(0);

			}
			break;
	}
	return 0;
}

int32 CVICALLBACK DoneCallback (TaskHandle taskHandle, int32 status, void *callbackData)
{
	/*MessagePopup("EXIT","Task finished");*/
	return 0;
}

int CVICALLBACK RangeCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			break;
	}
	return 0;
}

int CVICALLBACK OnGenTimer (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	
	int numWritten=0;

	switch (event)
	{
		case EVENT_TIMER_TICK:
			if(nrPoints == 0)
			{
				return -1;
			}


			outVal = buffer[index];
			index = (index + 1) % nrPoints;


			err = DAQmxErrChk(DAQmxWriteAnalogF64(taskHandle,1,1,10,DAQmx_Val_GroupByChannel,&outVal,&numWritten,NULL));
			if(err < 0)
			{
				return -1;
			}

			break;
	}
	return 0;
}

static void BuildStepBuffer(unsigned int nrPoints, double step, double *buf)
{
	if(nrPoints == 0)
	{
		return;
	}
	buf[0]=0;
	for(int i=1; i<nrPoints; i++)
	{
		buf[i] = buf[i-1]+step;
	}
}

int CVICALLBACK StartCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int buttonState = 0;
	char channel[100]="\0";
	double min,max;

	double freq = 0;

	int val=0;
	double phase = 2;
	switch (event)
	{
		case EVENT_COMMIT:

			GetCtrlVal(mainPanel,control,&buttonState);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_CHANNEL,channel);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_MIN,&min);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_MAX,&max);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_AMPLITUDE,&amp);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_FREQUENCY,&freq);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_POINTS_PERIOD,&nrPoints);
			GetCtrlVal(mainPanel,MAIN_PANEL_IDC_SIGNAL_TYPE,&val);


			if(nrPoints ==0 || freq <=0.0)
			{
				MessagePopup("Input Error","Freq / nrPoints must be positive");
				return 0;
			}

			signalType = val-1;
			outVal = 0;
			index = 0;
			if(buttonState == 1)
			{
				switch(signalType)
				{
					case SINUS:
						SineWave(nrPoints,amp,1./nrPoints,&phase,buffer);
						break;
					case TRIUNGHIULAR:
						TriangleWave(nrPoints,amp,1./nrPoints,&phase,buffer);
						break;
					case DREPTUNGHIULAR:
						SquareWave(nrPoints,amp,1./nrPoints,&phase,50.0,buffer);
						break;
					default: //TREAPTA
						BuildStepBuffer(nrPoints,0.1,buffer);
						break;
				}


				for(int i=0; i<nrPoints; i++)
				{
					buffer[i]=buffer[i]+amp;
				}

				DeleteGraphPlot(mainPanel,MAIN_PANEL_IDC_GRAPH,-1,VAL_DELAYED_DRAW);
				PlotY(mainPanel,MAIN_PANEL_IDC_GRAPH,buffer,nrPoints,VAL_DOUBLE,VAL_THIN_LINE,VAL_DOTTED_SOLID_CIRCLE,VAL_DASH,VAL_CONNECTED_POINTS,VAL_RED);


				SetCtrlAttribute(panel,MAIN_PANEL_IDC_GEN_TIMER,ATTR_INTERVAL,1.0/(nrPoints*freq));

				err = DAQmxErrChk(DAQmxCreateTask("",&taskHandle));
				if(err < 0) return -1;

				err = DAQmxErrChk(DAQmxCreateAOVoltageChan(taskHandle,channel,"",min,max,DAQmx_Val_Volts,NULL));
				if(err < 0) return -1;


				err = DAQmxErrChk(DAQmxRegisterDoneEvent(taskHandle,0,DoneCallback,NULL));
				if(err < 0) return -1;

				err = DAQmxErrChk(DAQmxStartTask(taskHandle));
				if(err < 0) return -1;

				SetCtrlAttribute(panel,MAIN_PANEL_IDC_GEN_TIMER,ATTR_ENABLED,1);

			}
			else
			{
				err = DAQmxErrChk(DAQmxStopTask(taskHandle));
				if(err < 0) return -1;

				err = DAQmxErrChk(DAQmxClearTask(taskHandle));
				if(err < 0) return -1;

				SetCtrlAttribute(panel,MAIN_PANEL_IDC_GEN_TIMER,ATTR_ENABLED,0);
			}
			break;
	}
	return 0;
}
