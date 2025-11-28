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
#define  MAIN_PANEL_IDC_MIN               3       /* control type: numeric, callback function: RangeCallback */
#define  MAIN_PANEL_IDC_MAX               4       /* control type: numeric, callback function: RangeCallback */
#define  MAIN_PANEL_IDC_GRAPH             5       /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_GEN_TIMER         6       /* control type: timer, callback function: OnGenTimer */
#define  MAIN_PANEL_IDC_SIGNAL_TYPE       7       /* control type: ring, callback function: (none) */
#define  MAIN_PANEL_IDC_AMPLITUDE         8       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_POINTS_PERIOD     9       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_FREQUENCY         10      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_DECORATION            11      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG               12      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_DECORATION_2          13      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_3             14      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_IDC_BTT_START         15      /* control type: textButton, callback function: StartCallback */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnGenTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK RangeCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK StartCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif