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

#define  MAIN_PANEL                       1       /* callback function: MainPanelCB */
#define  MAIN_PANEL_IDC_CHANNEL           2       /* control type: string, callback function: (none) */
#define  MAIN_PANEL_IDC_VMAX              3       /* control type: numeric, callback function: OnRange */
#define  MAIN_PANEL_IDC_VMIN              4       /* control type: numeric, callback function: OnRange */
#define  MAIN_PANEL_IDC_DISPLAY_CHART     5       /* control type: strip, callback function: (none) */
#define  MAIN_PANEL_IDC_SAMPLES_PER_CHN   6       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_SAMPLING_RATE     7       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_BTT_QUIT          8       /* control type: command, callback function: QuitCallback */
#define  MAIN_PANEL_DECORATION_2          9       /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_IDC_BTT_START_STOP    10      /* control type: textButton, callback function: OnStartStopButton */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnRange(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnStartStopButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif