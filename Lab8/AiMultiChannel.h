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
#define  MAIN_PANEL_IDC_GRAPH             2       /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_SAMP_PER_CHANNEL  3       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_RATE              4       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_MAX               5       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_MIN               6       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_CHANNELS          7       /* control type: string, callback function: (none) */
#define  MAIN_PANEL_IDC_START_TASK        8       /* control type: textButton, callback function: OnStartAi */
#define  MAIN_PANEL_IDC_STRIPCHART        9       /* control type: strip, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK MainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnStartAi(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
