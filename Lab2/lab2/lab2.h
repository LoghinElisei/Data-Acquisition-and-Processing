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

#define  PANEL                            1       /* callback function: OnMainPanel */
#define  PANEL_GRAPH                      2       /* control type: graph, callback function: (none) */
#define  PANEL_BINARYSWITCH_2             3       /* control type: binary, callback function: ONAquisitionMode */
#define  PANEL_BINARYSWITCH               4       /* control type: binary, callback function: OnSwitch */
#define  PANEL_LED                        5       /* control type: LED, callback function: (none) */
#define  PANEL_DECORATION                 6       /* control type: deco, callback function: (none) */
#define  PANEL_COMMANDBUTTON_2            7       /* control type: command, callback function: (none) */
#define  PANEL_COMMANDBUTTON              8       /* control type: command, callback function: (none) */
#define  PANEL_DECORATION_2               9       /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_3               10      /* control type: deco, callback function: (none) */
#define  PANEL_NUMERIC_2                  11      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC                    12      /* control type: numeric, callback function: (none) */
#define  PANEL_TXT                        13      /* control type: textMsg, callback function: (none) */
#define  PANEL_NUMERIC_5                  14      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_4                  15      /* control type: numeric, callback function: (none) */
#define  PANEL_NUMERIC_3                  16      /* control type: numeric, callback function: (none) */
#define  PANEL_DECORATION_4               17      /* control type: deco, callback function: (none) */
#define  PANEL_TEXTMSG                    18      /* control type: textMsg, callback function: (none) */
#define  PANEL_COLORNUM_2                 19      /* control type: color, callback function: OnColor */
#define  PANEL_COLORNUM                   20      /* control type: color, callback function: OnColor */
#define  PANEL_DECORATION_5               21      /* control type: deco, callback function: (none) */
#define  PANEL_DECORATION_6               22      /* control type: deco, callback function: (none) */
#define  PANEL_TOGGLEBUTTON_2             23      /* control type: textButton, callback function: (none) */
#define  PANEL_TOGGLEBUTTON               24      /* control type: textButton, callback function: (none) */
#define  PANEL_TEXTMSG_2                  25      /* control type: textMsg, callback function: (none) */
#define  PANEL_RINGSLIDE                  26      /* control type: slide, callback function: OnAquisitionSlide */
#define  PANEL_NUMERIC_6                  27      /* control type: numeric, callback function: OnNumericBox */
#define  PANEL_DECORATION_7               28      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_FISIER                   2
#define  MENUBAR_FISIER_NOU               3       /* callback function: OnMenuBar */
#define  MENUBAR_FISIER_SALVARE           4       /* callback function: OnMenuBar */
#define  MENUBAR_FISIER_INCARCARE         5       /* callback function: OnMenuBar */
#define  MENUBAR_SEMNAL                   6
#define  MENUBAR_DESPRE                   7
#define  MENUBAR_DESPRE_ITEM5             8


     /* Callback Prototypes: */

int  CVICALLBACK ONAquisitionMode(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnAquisitionSlide(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnColor(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnMainPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK OnMenuBar(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK OnNumericBox(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnSwitch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif