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
#define  MAIN_PANEL_DECORATION_19         6       /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_16         7       /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_15         8       /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_IDC_NSAMPLES          9       /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_RATE              10      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_RAW_SIGNAL        11      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_FREQ_PEAK         12      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_POWER_PEAK        13      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_CURSORVAL         14      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_OFFSET_THRESHOLD  15      /* control type: scale, callback function: OnOffsetChangeCB */
#define  MAIN_PANEL_IDC_NOISE_AMPLITUDE   16      /* control type: scale, callback function: OnNoiseAmplitudeChangeCB */
#define  MAIN_PANEL_IDC_ALPFA_COEF        17      /* control type: scale, callback function: OnAlphaChangeCB */
#define  MAIN_PANEL_IDC_NAVG_WND          18      /* control type: slide, callback function: OnNAvgWndChangeCB */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_NOISE  19      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_TWO    20      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHK_SIGNAL_ONE    21      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHK_OFFSET        22      /* control type: radioButton, callback function: SettingRawSignalCB */
#define  MAIN_PANEL_IDC_CHOSE_FILTER      23      /* control type: tree, callback function: OnChoseFilterCB */
#define  MAIN_PANEL_TEXTMSG               24      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_DECORATION_20         25      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_18         26      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_17         27      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_Filters_2             28      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_IDC_TXT_FILTERS       29      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_IDC_FILTER_BAND       30      /* control type: slide, callback function: OnFilterBandCB */
#define  MAIN_PANEL_IDC_FB_F4             31      /* control type: numeric, callback function: OnFxChangeCB */
#define  MAIN_PANEL_IDC_FB_F3             32      /* control type: numeric, callback function: OnFxChangeCB */
#define  MAIN_PANEL_IDC_FB_F2             33      /* control type: numeric, callback function: OnFxChangeCB */
#define  MAIN_PANEL_IDC_FB_F1             34      /* control type: numeric, callback function: OnFxChangeCB */
#define  MAIN_PANEL_IDC_FILTER_ORDER      35      /* control type: scale, callback function: OnChangeFilterOrderCB */
#define  MAIN_PANEL_IDC_NCOEF             36      /* control type: numeric, callback function: OnChangeNCoefCB */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnAlphaChangeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnChangeFilterOrderCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnChangeNCoefCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnChoseFilterCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnFilterBandCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnFxChangeCB(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
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