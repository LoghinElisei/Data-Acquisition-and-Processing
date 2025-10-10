#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "lab2.h"

static int panelHandle;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "lab2.uir", PANEL)) < 0)
		return -1;
	DisplayPanel (panelHandle);

	RunUserInterface ();
	DiscardPanel (panelHandle);

	return 0;

}

int CVICALLBACK OnMainPanel (int panel, int event, void *callbackData,
							 int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_GOT_FOCUS:

			break;
		case EVENT_LOST_FOCUS:

			break;
		case EVENT_CLOSE:
			if(ConfirmPopup("Exit","Do you really want to quit?"))
			{
				QuitUserInterface(0);
			}
			break;
	}
	return 0;
}




int CVICALLBACK OnSwitch (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			int val;

			GetCtrlVal (panel, PANEL_BINARYSWITCH , &val);
			SetCtrlVal(panel, PANEL_LED,val);

			SetCtrlAttribute(panel,PANEL_BINARYSWITCH_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COLORNUM,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COLORNUM_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COMMANDBUTTON,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COMMANDBUTTON_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_GRAPH,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_3,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_4,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_5,ATTR_DIMMED,!val);

			/*SetCtrlAttribute(panel,PANEL_RINGSLIDE,ATTR_DIMMED,!val);*/
			SetCtrlAttribute(panel,PANEL_TOGGLEBUTTON,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_TOGGLEBUTTON_2,ATTR_DIMMED,!val);


			if(val == 0)
			{
				SetCtrlVal(panel,PANEL_BINARYSWITCH_2,0);
			}
			break;
	}
	return 0;
}

static int on=1;
int CVICALLBACK ONAquisitionMode (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{

	switch (event)
	{
		case EVENT_COMMIT:

			on=on^1;
			SetCtrlAttribute(panel,PANEL_RINGSLIDE,ATTR_DIMMED,on);
			SetCtrlAttribute(panel,PANEL_NUMERIC_6,ATTR_DIMMED,on);
			if(on == 0)
			{
				SetCtrlAttribute(panel,PANEL_COMMANDBUTTON,ATTR_DIMMED,1);
				SetCtrlAttribute(panel,PANEL_COMMANDBUTTON_2,ATTR_DIMMED,1);
			}
			else
			{
				SetCtrlAttribute(panel,PANEL_COMMANDBUTTON,ATTR_DIMMED,0);
				SetCtrlAttribute(panel,PANEL_COMMANDBUTTON_2,ATTR_DIMMED,0);
			}
			break;

	}
	return 0;
}

void CVICALLBACK OnMenuBar (int menuBar, int menuItem, void *callbackData,
							int panel)
{
	int val = 0;
	switch (menuItem)
	{
		case MENUBAR_FISIER_NOU:

			SetCtrlAttribute(panel,PANEL_BINARYSWITCH_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COLORNUM,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COLORNUM_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COMMANDBUTTON,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_COMMANDBUTTON_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_GRAPH,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_2,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_3,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_4,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_5,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_NUMERIC_6,ATTR_DIMMED,!val);
			/*SetCtrlAttribute(panel,PANEL_RINGSLIDE,ATTR_DIMMED,!val);*/
			SetCtrlAttribute(panel,PANEL_TOGGLEBUTTON,ATTR_DIMMED,!val);
			SetCtrlAttribute(panel,PANEL_TOGGLEBUTTON_2,ATTR_DIMMED,!val);
			SetCtrlVal(panel,PANEL_BINARYSWITCH,0);
			SetCtrlVal(panel,PANEL_LED,0);

			break;
		case MENUBAR_FISIER_SALVARE:
			MessagePopup("Info", "Ai selectatfgdfdsgsfdgsfdg File ? New");

			break;
	}
}

int CVICALLBACK OnNumericBox (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	double val;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,PANEL_NUMERIC_6,&val);
			SetCtrlVal(panel,PANEL_RINGSLIDE,val);


			break;
	}
	return 0;
}

int CVICALLBACK OnAquisitionSlide (int panel, int control, int event,
								   void *callbackData, int eventData1, int eventData2)
{
	double val;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,PANEL_RINGSLIDE,&val);
			SetCtrlVal(panel,PANEL_NUMERIC_6,val);
			break;
	}
	return 0;
}

int CVICALLBACK OnColor (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	int colorCursor,color_tray;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,PANEL_COLORNUM,&colorCursor);
			GetCtrlVal(panel,PANEL_COLORNUM_2,&color_tray);
			
			SetCursorAttribute(panel,PANEL_GRAPH,1,ATTR_CURSOR_COLOR,colorCursor);
			/*SetPlotAttribute(panel,PANEL_GRAPH,1,ATTR_TRACE_COLOR,color_tray);*/
			
			break;
	}
	return 0;
}
