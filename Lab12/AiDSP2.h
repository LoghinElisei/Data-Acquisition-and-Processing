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

#define  MAIN_PANEL                       1       /* callback function: OnMainPanelCB */
#define  MAIN_PANEL_IDC_CHANNEL           2       /* control type: string, callback function: (none) */
#define  MAIN_PANEL_IDC_START_TASK        3       /* control type: textButton, callback function: OnStartTaskCB */
#define  MAIN_PANEL_DECORATION_16         4       /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_IDC_NSAMPLES          5       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_RATE              6       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_NOISE_AMPLITUDE_2 7       /* control type: scale, callback function: OnNoiseAmplitudeChangeCB */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_NOISE2 8       /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_NOISE_AMPLITUDE_1 9       /* control type: scale, callback function: OnNoiseAmplitudeChangeCB */
#define  MAIN_PANEL_IDC_RAW_SIGNAL_2      10      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_CONVOLVE_SIGNAL   11      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_CORRELATE_SIGNAL  12      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_RAW_SIGNAL_1      13      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_NOISE1 14      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_TEXTMSG               15      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_DECORATION_18         16      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_17         17      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_Filters_2             18      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_IDC_TXT_FILTERS       19      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnMainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnNoiseAmplitudeChangeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnStartTaskCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingRawSignalCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif