#include <ansi_c.h>
#include <NIDAQmx.h>
#include "daqmxioctrl.h"
#include <cvidef.h>
#include <cvirte.h>		
#include <userint.h>
#include "Do.h"

static int doPanel;
static _Bool buttonState = FALSE;
static TaskHandle doTask;
static int32 sampsPerChanWritten = 0;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((doPanel = LoadPanel (0, "Do.uir", DO_PANEL)) < 0)
		return -1;
	
	NIDAQmx_NewPhysChanDOPortCtrl(doPanel,DO_PANEL_IDC_DO_CHANNEL,8);
	
	DisplayPanel (doPanel);
	RunUserInterface ();
	DiscardPanel (doPanel);
	return 0;
}

int CVICALLBACK OnDoPanelCB (int panel, int event, void *callbackData,
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

int CVICALLBACK OnDoButtonWrite (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	unsigned char val;
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal(doPanel,DO_PANEL_IDC_DO_VALUE,&val);
			
			
			int portValue = val;
			
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_0,(portValue & 0x01));
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_1,(portValue & 0x02) >> 1);
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_2, (portValue & 0x04) >> 2);
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_3,(portValue & 0x08) >>3);
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_4,(portValue & 0x10) >>4);
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_5,(portValue & 0x20) >>5);
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_6,(portValue & 0x40) >>6);
			SetCtrlVal(doPanel,DO_PANEL_IDC_LED_7,(portValue & 0x80) >>7);
			
			val=(~val);
			DAQmxWriteDigitalU8(doTask,1,1,10,DAQmx_Val_GroupByChannel,&val,&sampsPerChanWritten,NULL);
			
			break;
	}
	return 0;
}

int CVICALLBACK OnDoLed (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			break;
	}
	return 0;
}

int CVICALLBACK OnDoButtonStart (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	char channel[100];
	switch (event)
	{
		case EVENT_COMMIT:

			buttonState=!buttonState;
			switch(buttonState)
			{

				case TRUE:
					GetCtrlVal(doPanel, DO_PANEL_IDC_DO_CHANNEL,channel);
					DAQmxCreateTask("",&doTask);
					
					DAQmxCreateDOChan(doTask, channel, "",DAQmx_Val_ChanForAllLines);
				
					DAQmxStartTask(doTask);
	

					break;
				case FALSE:

					DAQmxStopTask(doTask);
					
					DAQmxClearTask(doTask);
			
					break;
			}



			break;
	}
	return 0;
}
