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

#define  DO_PANEL                         1       /* callback function: OnDoPanelCB */
#define  DO_PANEL_IDC_DO_CHANNEL          2       /* control type: string, callback function: (none) */
#define  DO_PANEL_IDC_DO_WRITE_BTT        3       /* control type: command, callback function: OnDoButtonWrite */
#define  DO_PANEL_IDC_LED_5               4       /* control type: LED, callback function: OnDoLed */
#define  DO_PANEL_IDC_LED_6               5       /* control type: LED, callback function: OnDoLed */
#define  DO_PANEL_IDC_LED_7               6       /* control type: LED, callback function: OnDoLed */
#define  DO_PANEL_IDC_DO_START            7       /* control type: textButton, callback function: OnDoButtonStart */
#define  DO_PANEL_IDC_DO_VALUE            8       /* control type: numeric, callback function: (none) */
#define  DO_PANEL_IDC_LED_0               9       /* control type: LED, callback function: OnDoLed */
#define  DO_PANEL_DECORATION_8            10      /* control type: deco, callback function: (none) */
#define  DO_PANEL_IDC_LED_1               11      /* control type: LED, callback function: OnDoLed */
#define  DO_PANEL_DECORATION_7            12      /* control type: deco, callback function: (none) */
#define  DO_PANEL_IDC_LED_2               13      /* control type: LED, callback function: OnDoLed */
#define  DO_PANEL_DECORATION              14      /* control type: deco, callback function: (none) */
#define  DO_PANEL_IDC_LED_3               15      /* control type: LED, callback function: OnDoLed */
#define  DO_PANEL_TEXTMSG                 16      /* control type: textMsg, callback function: (none) */
#define  DO_PANEL_IDC_LED_4               17      /* control type: LED, callback function: OnDoLed */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnDoButtonStart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDoButtonWrite(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDoLed(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDoPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif