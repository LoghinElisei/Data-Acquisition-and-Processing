/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  MAIN_PANEL                       1       /* callback function: OnMainPanel */
#define  MAIN_PANEL_EXIT_BUTTON           2       /* control type: command, callback function: OnExit */
#define  MAIN_PANEL_POWER_LED             3       /* control type: LED, callback function: (none) */
#define  MAIN_PANEL_POWER_SWITCH          4       /* control type: binary, callback function: OnPowerSwitch */
#define  MAIN_PANEL_FONT                  5       /* control type: color, callback function: OnDisplay */
#define  MAIN_PANEL_BACKGROUND            6       /* control type: color, callback function: OnDisplay */
#define  MAIN_PANEL_DC                    7       /* control type: scale, callback function: (none) */
#define  MAIN_PANEL_OUTPUT                8       /* control type: scale, callback function: (none) */
#define  MAIN_PANEL_NUM_DEL               9       /* control type: command, callback function: OnDelPress */
#define  MAIN_PANEL_NUM_EQUAL             10      /* control type: command, callback function: OnEqualPress */
#define  MAIN_PANEL_NUM_MINUS             11      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_DIV               12      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_0                 13      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_9                 14      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_8                 15      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_6                 16      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_5                 17      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_3                 18      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_2                 19      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_7                 20      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_TIMES             21      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_PLUS              22      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_4                 23      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_NUM_1                 24      /* control type: command, callback function: OnKeyPress */
#define  MAIN_PANEL_DECORATION            25      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_5          26      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_3          27      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_2          28      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_4          29      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_RINGSLIDE             30      /* control type: slide, callback function: (none) */
#define  MAIN_PANEL_DISPLAY               31      /* control type: string, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_MENU1                    2


     /* Callback Prototypes: */

int  CVICALLBACK OnDelPress(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDisplay(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnEqualPress(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnExit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnKeyPress(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnMainPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPowerSwitch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif