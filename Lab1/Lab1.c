#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>

#include "Lab1.h"
#include <string.h>
#include <stdio.h>

static int mainPanel;

int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((mainPanel = LoadPanel (0, "Lab1.uir", MAIN_PANEL)) < 0)
		return -1;
	DisplayPanel (mainPanel);
	RunUserInterface ();
	DiscardPanel (mainPanel);
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
			if(ConfirmPopup ("Quit", "Do you Really want to quit ?"))
			{
				QuitUserInterface (0);
			}

			break;
	}
	return 0;
}

int CVICALLBACK OnExit (int panel, int control, int event,
						void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if(ConfirmPopup ("Quit", "Do you Really want to quit ?"))
			{
				QuitUserInterface (0);
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnPowerSwitch (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	int val;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (mainPanel, MAIN_PANEL_POWER_SWITCH, &val);
			SetCtrlVal (mainPanel, MAIN_PANEL_POWER_LED, val);
			break;
	}
	return 0;
}



char freq[1024]="\0";


int CVICALLBACK OnDisplay (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int colorBg,colorFont;
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlVal (panel, MAIN_PANEL_BACKGROUND, &colorBg);
			GetCtrlVal (panel, MAIN_PANEL_FONT,&colorFont);

			SetCtrlAttribute(panel,MAIN_PANEL_DISPLAY,ATTR_TEXT_BGCOLOR,colorBg);
			SetCtrlAttribute(panel,MAIN_PANEL_DISPLAY,ATTR_TEXT_COLOR,colorFont);


			break;
	}
	return 0;
}


int CVICALLBACK OnKeyPress (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	char key = '\0';
	switch (event)
	{
		case EVENT_COMMIT:

			switch (control)
			{
				case MAIN_PANEL_NUM_0 :
					key = '0';
					break;
				case MAIN_PANEL_NUM_1 :
					key = '1';
					break;
				case MAIN_PANEL_NUM_2 :
					key = '2';
					break;
				case MAIN_PANEL_NUM_3 :
					key = '3';
					break;
				case MAIN_PANEL_NUM_4 :
					key = '4';
					break;
				case MAIN_PANEL_NUM_5 :
					key = '5';
					break;
				case MAIN_PANEL_NUM_6 :
					key = '6';
					break;
				case MAIN_PANEL_NUM_7 :
					key = '7';
					break;
				case MAIN_PANEL_NUM_8 :
					key = '8';
					break;
				case MAIN_PANEL_NUM_9 :
					key = '9';
					break;
				case MAIN_PANEL_NUM_PLUS :
					key = '+';
					break;
				case MAIN_PANEL_NUM_MINUS :
					key = '-';
					break;
				case MAIN_PANEL_NUM_TIMES :
					key = '*';
					break;
				case MAIN_PANEL_NUM_DIV :
					key = '/';
					break;
			}

			char op[]="+-*/";



			size_t len = strlen(freq);

			if( strchr(op,key) && strchr(op,freq[len-1]))
			{
				if(MessagePopup ("Error", "Incorrect operation (*+-/) "))
				{
					;
				}
			}
			else
			{
				if ( len < ( sizeof(freq) -1 ))
				{
					freq[len]=key;
					freq[len+1]='\0';
				}


				SetCtrlVal(panel,MAIN_PANEL_DISPLAY,freq);
			}
			break;
	}
	return 0;
}

int CVICALLBACK OnDelPress (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			size_t len = strlen(freq);
			if ( len >0 )
			{
				freq[len-1]='\0';

			}
			SetCtrlVal(panel,MAIN_PANEL_DISPLAY,freq);
			break;
	}
	return 0;
}

int CVICALLBACK OnEqualPress (int panel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			char *val;
			double sum = 0;

			char aux[1024];
			strcpy(aux,freq);
			
			aux[strlen(freq)]='\0';
				
			val = strtok(aux,"+-/*");
			if(val != NULL)
			{
				sum = atof(val);
			}
			else
			{
				if(MessagePopup ("Error", "No operator provided (*+-/) "))
				{
					;
				}
			}
			int index = (int)strlen(val);
			while( (val = strtok(NULL,"+-/*")) !=NULL)
			{
				char operator = freq[index];
				double number = atof(val);

				switch(operator)
				{
					case '+':
						sum+=number;
						break;
					case '-':
						sum-=number;
						break;
					case '*':
						sum*=number;
						break;
					case '/':
						if(number == 0)
						{
							if(MessagePopup ("Arithmetic Error", "!!! Invalid operation : Divided by 0 !!!"))
							{
								;
							}
							return 1;
						}
						sum=sum/number;
						break;
				}

				index+=(int)strlen(val)+1;
			}
			
			sprintf(freq,"%.2f",sum);
			SetCtrlVal(panel,MAIN_PANEL_DISPLAY,freq);
			break;
			
	}
	return 0;
}
