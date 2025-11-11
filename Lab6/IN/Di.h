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

#define  DI_PANEL                         1       /* callback function: OnDiPanelCB */
#define  DI_PANEL_IDC_DI_CHANNEL          2       /* control type: string, callback function: (none) */
#define  DI_PANEL_IDC_DI_READ_BTT         3       /* control type: command, callback function: OnDiButtonRead */
#define  DI_PANEL_IDC_KEY_LED_0           4       /* control type: LED, callback function: (none) */
#define  DI_PANEL_IDC_KEY_LED_1           5       /* control type: LED, callback function: (none) */
#define  DI_PANEL_IDC_KEY_LED_2           6       /* control type: LED, callback function: (none) */
#define  DI_PANEL_IDC_KEY_LED_3           7       /* control type: LED, callback function: (none) */
#define  DI_PANEL_IDC_DI_START            8       /* control type: textButton, callback function: OnDiButtonStart */
#define  DI_PANEL_IDC_DI_VALUE            9       /* control type: numeric, callback function: (none) */
#define  DI_PANEL_DECORATION_10           10      /* control type: deco, callback function: (none) */
#define  DI_PANEL_DECORATION_12           11      /* control type: deco, callback function: (none) */
#define  DI_PANEL_DECORATION_11           12      /* control type: deco, callback function: (none) */
#define  DI_PANEL_TEXTMSG_2               13      /* control type: textMsg, callback function: (none) */
#define  DI_PANEL_IDC_KEY_TIMER           14      /* control type: timer, callback function: OnDiKeyTimer */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnDiButtonRead(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDiButtonStart(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDiKeyTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDiPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif