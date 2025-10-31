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

#include <userint.h>
#include <ansi_c.h>
#include <utility.h>
#include "ProcessData.h"
#include "SerialECG.h"
#include "RealTimeECGProcess.h"

//==============================================================================
// Constants
#define PACK_BEGING		'<'
#define PACK_END		'>'

#define AUTOMAT_PACK_START	1
#define AUTOMAT_PACK_DATA	2

//==============================================================================
// Types

//==============================================================================
// Static global variables
static char pack[ 128 ] = { 0 };
static unsigned char packIndex = 0;
static automateState = AUTOMAT_PACK_START;
const int sizeBuffer = 300;
int fs = 128;
int delay, num_qrs, num_r_peaks;
int ecg_initialized = 0;
int ecg_peak_detected = 0;
int ecg_sample_counter = 0;
static double values[128] = {0};
//==============================================================================
// Static functions

//==============================================================================
// Global variables
double ecg_sample;
double heart_rate = 0.0;
//==============================================================================
// Global functions
// 
//	formatul pachetului este <123 123 123>
//
int ProcessComInBuffer( char *comBuffer, int comBufferLength )
{
	int err = 0;
	int i = 0, k = 0;
	//static int iCh0 = 0, iCh1 = 0, iCh2 = 0;
	
	static int iCh[3];
	char pack[20];
	char DateCanal[4] = {0, 0, 0, 0} ;
	DateCanal[3] = '\0';
	int indexDate = 0;
	int chCurent = 0;

	
	for( i = 0; i < comBufferLength; i++ )
	{
		switch( automateState )
		{
			case AUTOMAT_PACK_START:
				
				//...
				
				if (comBuffer[i] == '<')
				{
					automateState = AUTOMAT_PACK_DATA;
				}

				break;
			case AUTOMAT_PACK_DATA:
				
				//...
				BOOL found = 0;
				while (comBuffer[i] != '>' && i < comBufferLength)
				{
					pack[k] = comBuffer[i];
					k++;
					i++;
					found = 1;
				}
				i--;
				if(found == 1)
				{
					pack[k] = '\0';
					
					sscanf(pack, "%d %d %d", &iCh[0], &iCh[1], &iCh[2]);
					
					PlotStripChartPoint( mainPanel, MAIN_PANEL_IDC_DISP_ECG1, (double)iCh[0] ); //*
					PlotStripChartPoint( mainPanel, MAIN_PANEL_IDC_DISP_ECG2, (double)iCh[1] ); //*
					PlotStripChartPoint( mainPanel, MAIN_PANEL_IDC_DISP_ECG3, (double)iCh[2] ); //*
					
					double bandpass_output, derivative_output, squared_output, integrated_output;
					
					// To do 1: Conversia Datelor
    				
					// Conversia valorilor de tip integer extrase din serial in valori de tip double
					/*for(int j=0;j<k;j++)
					{
						values[j]=pack[j]/1024.0;	
					}*/
					
					ecg_sample = (double)iCh[0]/1024.0;
					
				    /* Initializarea parametrilor pentru functia de analiza a semnalului ECG */
				    if (!ecg_initialized) {
				        real_time_ecg_init();
						ecg_initialized = 1;
				    }
    
    				ecg_sample_counter++; 
					
					// To do 2: Includerea algoritmului
					
					/* Procesul de analiza a semnalului ECG pentru a se extrage complexul QRS */
					
					process_ecg_sample( ecg_sample,&heart_rate);
					
				  /*  // Filtru trece banda cu frecventele de taiere intre 5 si 15 Hz
				    bandpass_output = real_time_bandpass_filter(iCh[1]);
					// Derivata semnalului filtrat
				    derivative_output = real_time_derivative(bandpass_output,ecg_sample_counter);
					// Patratul derivatei
				    squared_output = derivative_output*derivative_output;
					// Valoarea mediei mobile a semnalului ridicat la patrat, utilizat pentru detectarea varfurilor undelor R
				    integrated_output = real_time_moving_average(squared_output,ecg_sample_counter);
					// Detectarea valorii maxime din compelxul QRS si calcului frecventei cardiace
					ecg_peak_detected   real_time_peak_detection(
					// Salvarea datelor pe Strip Chart si Display*/
					get_ecg_results(&heart_rate,&num_r_peaks,NULL, NULL);
					
				  	printf("%f",heart_rate);
					
					if(heart_rate != 0.0){
						
						//To do 3: Afisarea ritmului cardiac
						PlotStripChartPoint( mainPanel, MAIN_PANEL_IDC_DISP_HRV_3,heart_rate ); //*
						SetCtrlVal(mainPanel,MAIN_PANEL_NUMERIC_3,heart_rate);
						// Afisarea grafica a variatiei frecventei cardiace
						// Afisarea valorii frecventei cardiace
					}
					
					
				}
				k = 0;
			
				
				automateState = AUTOMAT_PACK_START;
				break;
		}
	}
	
	return err;
}
