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
#define  MAIN_PANEL_IDC_OUTGRAPH_SPECTRUM 2       /* control type: graph, callback function: OnSpectrumGraphCB */
#define  MAIN_PANEL_IDC_FILTERED_SIGNAL   3       /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_CHANNEL           4       /* control type: string, callback function: (none) */
#define  MAIN_PANEL_IDC_START_TASK        5       /* control type: textButton, callback function: OnStartTaskCB */
#define  MAIN_PANEL_DECORATION_16         6       /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_15         7       /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_IDC_NSAMPLES          8       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_RATE              9       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_RAW_SIGNAL        10      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_FREQ_PEAK         11      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_POWER_PEAK        12      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_CURSORVAL         13      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_OFFSET_THRESHOLD  14      /* control type: scale, callback function: OnOffsetChangeCB */
#define  MAIN_PANEL_IDC_NOISE_AMPLITUDE   15      /* control type: scale, callback function: OnNoiseAmplitudeChangeCB */
#define  MAIN_PANEL_IDC_ALPFA_COEF        16      /* control type: scale, callback function: OnAlphaChangeCB */
#define  MAIN_PANEL_IDC_NAVG_WND          17      /* control type: slide, callback function: OnNAvgWndChangeCB */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_NOISE  18      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_TWO    19      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_ONE    20      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHK_OFFSET        21      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHOSE_FILTER      22      /* control type: tree, callback function: OnChoseFilterCB */
#define  MAIN_PANEL_TEXTMSG               23      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_DECORATION_18         24      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_17         25      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_Filters_2             26      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_IDC_TXT_FILTERS       27      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnAlphaChangeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnChoseFilterCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnMainPanelCB(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnNAvgWndChangeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnNoiseAmplitudeChangeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnOffsetChangeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSpectrumGraphCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnStartTaskCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SettingRawSignalCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif