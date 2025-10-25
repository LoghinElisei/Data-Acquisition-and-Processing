//==============================================================================
//
// Title:		ProcessData.c
// Purpose:		A short description of the implementation.
//
// Created on:	28.10.2013 at 18:53:14 by Terran.
// Copyright:	UTI. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files

#include <windows.h>

#include <userint.h>
#include <ansi_c.h>
#include <utility.h>
#undef Beep
#include <mmsystem.h>
#include "ProcessData.h"
#include "SerialECG.h"

//==============================================================================
// Constants
#define PACK_BEGING		'<'
#define PACK_END		'>'

#define AUTOMAT_PACK_START	1
#define AUTOMAT_PACK_DATA	2
#define THRESHOLD 400
//==============================================================================
// Types

//==============================================================================
// Static global variables
static char pack[ 128 ] = { 0 };
static unsigned char packIndex = 0;
static automateState = AUTOMAT_PACK_START;

//==============================================================================
// Static functions

//==============================================================================
// Global variables

//==============================================================================
// Global functions
//
//	formatul pachetului este >123 123 123<
//


int CVICALLBACK PlayHeartSound(void *data)
{

	Beep(1200, 300);
	Sleep(60);
	Beep(1000, 200); 

	return 0;
}

int ProcessComInBuffer( char *comBuffer, int comBufferLenght )
{
	int err = 0;
	int i = 0;
	static int iCh0 = 0, iCh1 = 0, iCh2 = 0;
	/*static int lastBeatTime =0 ;
	int currentTime = Timer();*/
	static int heartbeatPlaying = 0;
	for( i = 0; i < comBufferLenght; i++ )
	{
		switch( automateState )
		{
			case AUTOMAT_PACK_START:


				if(comBuffer[i] == '<')
				{
					automateState = AUTOMAT_PACK_DATA;
				}

				break;
			case AUTOMAT_PACK_DATA:
				if(comBuffer[i] == '>')
				{

					automateState = AUTOMAT_PACK_START;


					char delimiter[]="<> ";

					char *auxBuffer = (char*)calloc( comBufferLenght + 1, sizeof(char));
					strcpy(auxBuffer,comBuffer);
					char *nr = strtok(auxBuffer,delimiter);
					iCh0 = atoi(nr);

					if(nr != NULL)
					{
						nr=strtok(NULL,delimiter);
						iCh1 = atoi(nr);
					}

					if(nr != NULL)
					{
						nr=strtok(NULL,delimiter);
						iCh2 = atoi(nr);
					}

					i+=2;


					if(iCh0 > THRESHOLD )
					{
						if(!heartbeatPlaying)
						{

							CmtScheduleThreadPoolFunction(DEFAULT_THREAD_POOL_HANDLE,PlayHeartSound,NULL,NULL);
							heartbeatPlaying =1;
						}
					}
					else
					{
						if(heartbeatPlaying )
						{
							PlaySound(NULL,0,0);
							heartbeatPlaying =0;
						}
					}




					PlotStripChartPoint( mainPanel, MAIN_PANEL_IDC_DISP_ECG1, iCh0 );
					PlotStripChartPoint( mainPanel, MAIN_PANEL_IDC_DISP_ECG2, iCh1 );
					PlotStripChartPoint( mainPanel, MAIN_PANEL_IDC_DISP_ECG3, iCh2 );

				}


		}
	}

	return err;
}

