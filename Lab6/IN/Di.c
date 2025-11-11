#include <ansi_c.h>
#include <NIDAQmx.h>
#include "daqmxioctrl.h"
#include <cvidef.h>
#include <cvirte.h>
#include <userint.h>
#include "Di.h"

static int diPanel;
static TaskHandle diTask;
static int32 sampsPerChanReaded = 0;
static _Bool buttonState = FALSE;
static int err = 0;
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((diPanel = LoadPanel (0, "Di.uir", DI_PANEL)) < 0)
		return -1;

	NIDAQmx_NewPhysChanDIPortCtrl(diPanel,DI_PANEL_IDC_DI_CHANNEL,1);

	DisplayPanel (diPanel);
	RunUserInterface ();
	DiscardPanel (diPanel);
	return 0;
}


int DAQmxErrChk(int errCode)
{
	char errBuff[2048] = {'\0'};
	/*if(DAQmxGetExtendedErrorInfo(errBuff,2048) == 0)
		MessagePopup("Error",errBuff);
	*/
	return errCode;
}

int CVICALLBACK OnDiPanelCB (int panel, int event, void *callbackData,
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

int CVICALLBACK OnDiButtonRead (int panel, int control, int event, void *callbackData,
								int eventData1, int eventData2)
{
	uInt8 portValue = 0;
	switch (event)
	{

		case EVENT_COMMIT:

			err = DAQmxErrChk(DAQmxReadDigitalU8(diTask,1,10,DAQmx_Val_GroupByChannel,&portValue,1,&sampsPerChanReaded,NULL));
			if(err < 0)
			{
				return -1;
			}
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_0,(portValue & 0x01));
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_1,(portValue & 0x02) >> 1);
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_2, (portValue & 0x04) >> 2);
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_3,(portValue & 0x08) >>3);
			SetCtrlVal(diPanel,DI_PANEL_IDC_DI_VALUE,portValue);
			break;
	}
	return 0;
}


int CVICALLBACK OnDiButtonStart (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	char channel[100];
	switch (event)
	{
		case EVENT_COMMIT:

			buttonState=!buttonState;
			switch(buttonState)
			{

				case TRUE:
					GetCtrlVal(diPanel, DI_PANEL_IDC_DI_CHANNEL,channel);
					err = DAQmxErrChk (DAQmxCreateTask("",&diTask));
					if(err < 0)
					{
						return -1;
					}
					err = DAQmxErrChk(DAQmxCreateDIChan(diTask, channel, "",DAQmx_Val_ChanForAllLines));
					if(err < 0)
					{
						return -1;
					}
					err = DAQmxErrChk(DAQmxStartTask(diTask));
					if(err < 0)
					{
						return -1;
					}

					SetCtrlAttribute(diPanel,DI_PANEL_IDC_KEY_TIMER,ATTR_INTERVAL,0.5);
					SetCtrlAttribute(diPanel,DI_PANEL_IDC_KEY_TIMER,ATTR_ENABLED,1);
					break;
				case FALSE:

					SetCtrlAttribute(diPanel,DI_PANEL_IDC_KEY_TIMER,ATTR_ENABLED,0);

					err = DAQmxErrChk(DAQmxStopTask(diTask));
					if(err < 0)
					{
						return -1;
					}
					err = DAQmxErrChk(DAQmxClearTask(diTask));

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

int CVICALLBACK OnDiKeyTimer (int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{
	uInt8 portValue = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			err = DAQmxErrChk(DAQmxReadDigitalU8(diTask,1,10,DAQmx_Val_GroupByChannel,&portValue,1,&sampsPerChanReaded,NULL));
			if(err < 0)
			{
				return -1;
			}
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_0,(portValue & 0x01));
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_1,(portValue & 0x02) >> 1);
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_2, (portValue & 0x04) >> 2);
			SetCtrlVal(diPanel,DI_PANEL_IDC_KEY_LED_3,(portValue & 0x08) >>3);
			SetCtrlVal(diPanel,DI_PANEL_IDC_DI_VALUE,portValue);
			
			break;
	}
	return 0;
}
