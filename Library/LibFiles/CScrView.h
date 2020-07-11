// Scroll View


#pragma once
#include "DisplayDev.h"


// CScrView printing
/* The following functions are called for printing a page in the order given with one exception:
void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);  -- 1st
BOOL OnPreparePrinting(        CPrintInfo* pInfo);  -- 2nd
     CDC::StartDoc()                                -- 3rd
void OnPrepareDC(    CDC* pDC, CPrintInfo* pInfo);  -- 4th                         <-
     CDC::StartPage()                               -- 5th                          ^
void OnPrint(        CDC* pDC, CPrintInfo* pInfo);  -- 6th                          ^
     CDC::EndPage()                                 -- 7th then loops for each page ^
     CDC::EndDoc()                                  -- after last page
void OnEndPrinting(  CDC* pDC, CPrintInfo* pInfo);  -- last
*/


class CScrView : public CScrollView {

bool        printing;
uint        prtPage;
bool        endPrinting;

DisplayDev  display;
DisplayDev  printer;

String      font;
int         fontSize;                 // in 10* Points
CDC*        dc;
CPrintInfo* info;

static int  lastPos;

double      leftMargin;
double      rightMargin;
double      topMargin;
double      botMargin;

public:

String      rightFooter;                                          // Data to print at right side of footer
Date        date;                                                 // Date to print at left edge of footer

  CScrView() : printing(false), prtPage(0), endPrinting(false), font(_T("Arial")), fontSize(120) {}
 ~CScrView() { }

  void setFont(  TCchar* f, int points = 120) {font = f; fontSize = points < 70 ? points * 10 : points;}

  virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput();
  virtual void OnDraw(CDC* pDC);                                  // overridden to draw this view

          void invalidate() {Invalidate();}


  virtual void     trialRun(int& maxLines, int& noPages);
  virtual void     OnPrint(CDC* pDC, CPrintInfo* pInfo);
  virtual void     OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void     printFooter(Display& dev, int pageNo);         // Overload if different footer desired
          bool     isPrinting() {return printing;}

          void     setHorzMgns(double left, double right) {leftMargin = left; rightMargin = right;}
          void     setVertMgns(double top,  double bot)   {topMargin  = top;  botMargin   = bot;}

          Display& getDev() {return printing ? printer.getDisplay() : display.getDisplay();}

          void     suppressOutput() {if (printing) printer.suppressOutput();}
private:

  virtual BOOL      OnPreparePrinting(CPrintInfo* pInfo);


  virtual BOOL OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll = TRUE);

          void preparePrinter(CPrintInfo* pInfo);
          void preview(CPrintInfo* pInfo);
          void prepareDisplay();
          void setScrollSize();

          void print(             CPrintInfo* pInfo);
          void startFooter(       CPrintInfo* pInfo, Display& dev);
          bool isFinishedPrinting(CPrintInfo* pInfo);
protected:

  DECLARE_MESSAGE_MAP()
  };
