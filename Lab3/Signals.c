//==============================================================================
//
// Title:		Signals.c
// Purpose:		A short description of the implementation.
//
// Created on:	21.10.2013 at 12:19:18 by Terran.
// Copyright:	UTI. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include "toolbox.h"
#include <ansi_c.h>
#include <formatio.h>
#include <utility.h>
#include <analysis.h>
#include <userint.h>
#include "Signals.h"
#include "AcquisitionSimulation.h"

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables
static double rowSignal[ GRAPH_NPOINTS ];
//static char fileName[256] = {0};
static int traceColor = VAL_RED;

//==============================================================================
// Static functions

//==============================================================================
// Global variables
int signalType = SIGNALTYPE_SINEWAVE; //tipul semnalului selectat in meniu
int plotHandle = NO_PLOT;  //variabila ce contine handle-ul plotului de pe graph
double amplitude = 5.0;	   //amplitudinea semnalului generat
double frequency = 1.0/113.0; //frecventa de achizitie a semnalului generat
double dutyCycle = 50.0; //factorul de umplere al semnalului dreptunghiular
BOOL saveFlag = FALSE; //flag ce indica daca butonul de salvare a fost apasat

//==============================================================================
// Global functions

/*******************************************************************************
	functia de callback a butonului de achizite
*******************************************************************************/
int CVICALLBACK ManualAcquisitionCB (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	static double phase = 0.0;

	switch (event)
	{
		case EVENT_COMMIT:
			switch(signalType)
			{
				case SIGNALTYPE_SINEWAVE:
					SineWave(GRAPH_NPOINTS,amplitude,frequency,&phase,rowSignal);
				
					break;
				case SIGNALTYPE_SQUAREWAVE:
					SquareWave(GRAPH_NPOINTS,amplitude/2,frequency,&phase,50,rowSignal);
					
					break;
				case SIGNALTYPE_TRIANGLEWAVE:
					TriangleWave(GRAPH_NPOINTS,amplitude,frequency,&phase,rowSignal);
					
					break;
				default:
					WhiteNoise(GRAPH_NPOINTS,amplitude,100,rowSignal);
					
					break;
			}



			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a butonului de afisare
*******************************************************************************/
int CVICALLBACK ManualDisplayCB (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	double maxVal = 0.0;
	double minVal = 0.0;
	int maxIndex = 0;
	int minIndex = 0;
	double mean = 0.0;
	//static int count = 0;
	//char string[ MAX_PATHNAME_LEN ] = { 0 };

	/*for(int i=1;i<GRAPH_NPOINTS;i++)
	{
		if(rowSignal[i] < minVal)
		{
			minVal = rowSignal[i];
		}
		if(rowSignal[i] >maxVal)
		{
			maxVal = rowSignal[i];
		}
	}*/

	switch (event)
	{
		case EVENT_COMMIT:
		
			MaxMin1D(rowSignal,GRAPH_NPOINTS,&maxVal,&maxIndex,&minVal,&minIndex);
	if(plotHandle != NO_PLOT)
	{DeleteGraphPlot(panel,MAIN_PANEL,-1,VAL_DELAYED_DRAW);}
			plotHandle = PlotY(panel,MAIN_PANEL,rowSignal,GRAPH_NPOINTS,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,VAL_RED);
			
			mean=(maxVal+minVal)/2.0;
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MIN,minVal);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MEAN,mean);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MAX,maxVal);
			
			//To do: 08
			//*********

			//To do: 06
			//*********

			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a controlului esantion
*******************************************************************************/
int CVICALLBACK SampleCB (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	double val = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,MAIN_PANEL_IDC_NUM_SAMPLE_INDEX,&val);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_SAMPLE_VALUE,rowSignal[(int)val]);
			SetGraphCursor(panel,MAIN_PANEL_IDC_GRAPH_DISPLAY,1,val,rowSignal[(int)val]);

			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a controalelor color numeric (cursor si trasare)
*******************************************************************************/
int CVICALLBACK OnChooseColorCB (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	int val = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			
			
			GetCtrlVal(panel,control,&val);
			traceColor=val;
			switch(control)
			{
				case MAIN_PANEL_IDC_COLOR_CURSOR:
					SetCursorAttribute(panel,MAIN_PANEL,1,ATTR_CURSOR_COLOR,val);
					break;
				case MAIN_PANEL_IDC_COLOR_TRACE:
					if(plotHandle == NO_PLOT)
					{
						MessagePopup("WARNING!!!","Plot not displayed !!!");
					}
					else
					{
						SetPlotAttribute(panel,MAIN_PANEL_IDC_GRAPH_DISPLAY,plotHandle,ATTR_TRACE_COLOR,val);
					}
						break;
			}
			
			
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a butoanelor salvare si incarcare
*******************************************************************************/
int CVICALLBACK FileIoCB (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	int val = 0;
	int year = 0;
	int month = 0;
	int day = 0;
	int hour = 0;
	int minute = 0;
	int second = 0;
	char path[MAX_PATHNAME_LEN] = { 0 };
	int filestat = 0;
	double maxVal = 0.0;
	double minVal = 0.0;
	int maxIndex = 0;
	int minIndex = 0;
	double mean = 0.0;
	
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal( panel, control, &val );
			switch( control )
			{
				case MAIN_PANEL_IDC_BTT_FILESAVE:
					
					
					GetSystemDate(&month,&day,&year);
					GetSystemTime(&hour,&minute,&second);
					sprintf(path,"RowSignal_%4d.%2d.%2d_%2d-%2d-%2d.dat",year,month,day,hour,minute,second);
					saveFlag = val;
					SetCtrlAttribute(panel,MAIN_PANEL_IDC_BTT_FILELOAD,ATTR_DIMMED,val);
					ArrayToFile(path,rowSignal,VAL_DOUBLE,GRAPH_NPOINTS,1,VAL_GROUPS_TOGETHER,VAL_GROUPS_AS_COLUMNS,VAL_SEP_BY_TAB,0,VAL_ASCII,VAL_TRUNCATE);
					
					break;

				case MAIN_PANEL_IDC_BTT_FILELOAD:
					if(FileSelectPopup("","",".dat","Please select one file",VAL_LOAD_BUTTON,0,0,1,0,path))
					{
						filestat = FileToArray(path,rowSignal,VAL_DOUBLE,GRAPH_NPOINTS,1,VAL_GROUPS_TOGETHER,VAL_GROUPS_AS_COLUMNS,VAL_ASCII);
					
						if(filestat == -1)
						{
							MessagePopup("Error","Couldn't open the selected file\n");
						}
						else
						{
							plotHandle = PlotY(panel,MAIN_PANEL,rowSignal,GRAPH_NPOINTS,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,traceColor);
							MaxMin1D(rowSignal,GRAPH_NPOINTS,&maxVal,&maxIndex,&minVal,&minIndex);
							mean=(maxVal+minVal)/2.0;
							SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MIN,minVal);
							SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MEAN,mean);
							SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MAX,maxVal);
							
						}
					}

					break;
			}
			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a grafului (atunci cand exista un cursor definit)
*******************************************************************************/
int CVICALLBACK GraphDisplayCB (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	double x = 0;
	double y = 0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetGraphCursor(panel,MAIN_PANEL_IDC_GRAPH_DISPLAY,1,&x,&y);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_SAMPLE_INDEX,x);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_SAMPLE_VALUE,y);

			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a numeric slide-ului interval de achizitie
*******************************************************************************/
int CVICALLBACK AcquisitionTimerPeriodCB (int panel, int control, int event,
		void *callbackData, int eventData1, int eventData2)
{
	double val = 0.0;

	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal(panel,MAIN_PANEL_IDC_SL_ACQ_PERIOD,&val);
			SetCtrlAttribute(panel,MAIN_PANEL_SIMULATION_TIMER,ATTR_INTERVAL,val);

			break;
	}
	return 0;
}

/*******************************************************************************
	functia de callback a timerului de simulare
*******************************************************************************/
int CVICALLBACK OnSimulationTimerCB (int panel, int control, int event,
									 void *callbackData, int eventData1, int eventData2)
{
	static double phase = 1;
	double minVal=0;
	double maxVal=0;
	double mean=0;
	int maxIndex = 0;
	int minIndex = 0;
	switch (event)
	{
		case EVENT_TIMER_TICK:
			if(plotHandle != NO_PLOT)
			{DeleteGraphPlot(panel,MAIN_PANEL,-1,VAL_DELAYED_DRAW);}
			switch(signalType)
			{
				case SIGNALTYPE_SINEWAVE:
					SineWave(GRAPH_NPOINTS,amplitude,frequency,&phase,rowSignal);
					
					break;
				case SIGNALTYPE_SQUAREWAVE:
					SquareWave(GRAPH_NPOINTS,amplitude/2,frequency,&phase,50,rowSignal);
					
					break;
				case SIGNALTYPE_TRIANGLEWAVE:
					TriangleWave(GRAPH_NPOINTS,amplitude,frequency,&phase,rowSignal);
					
					break;
				default:
					WhiteNoise(GRAPH_NPOINTS,amplitude,100,rowSignal);
					
					break;
			}
			plotHandle = PlotY(panel,MAIN_PANEL,rowSignal,GRAPH_NPOINTS,VAL_DOUBLE,VAL_THIN_LINE,VAL_NO_POINT,VAL_SOLID,1,traceColor);

			
			MaxMin1D(rowSignal,GRAPH_NPOINTS,&maxVal,&maxIndex,&minVal,&minIndex);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MIN,minVal);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MEAN,mean);
			SetCtrlVal(panel,MAIN_PANEL_IDC_NUM_MAX,maxVal);
			
			break;
	}
	return 0;
}

