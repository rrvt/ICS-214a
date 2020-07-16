// Scroll View


#include "stdafx.h"
#include "CScrView.h"
#include "NotePad.h"


int CScrView::lastPos = 0;


BEGIN_MESSAGE_MAP(CScrView, CScrollView)
  ON_COMMAND(ID_FILE_PRINT,         &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()






void CScrView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) {

  if (printing) return;

  setScrollSize(); CScrollView::OnUpdate(pSender, lHint, pHint);
  }


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


// Get printer dialog box

BOOL CScrView::OnPreparePrinting(CPrintInfo* pInfo) {

  printing = true; outputDone = false;

  if (DoPreparePrinting(pInfo)) return true;

  printing = false; return false;
  }


void CScrView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {

  if (printing && !pInfo) return;

  dc = pDC;  info = pInfo;   CScrollView::OnPrepareDC(dc, pInfo);    printing = dc->IsPrinting();

  if (printing) preparePrinter(pInfo);
  else          prepareDisplay();

  if (printing && pInfo->m_bPreview) preview(pInfo);
  }



void CScrView::onPrepareOutput() {

  if (!printing)   {display.startDev(); return;}

  if (!endPrinting)
    printer.startDev();
  }


void CScrView::preparePrinter(CPrintInfo* pInfo) {
int pageNo = pInfo->m_nCurPage;

  pInfo->m_bContinuePrinting = true;     endPrinting = false;

  pInfo->m_nNumPreviewPages = 0;

  pInfo->SetMinPage(1);   pInfo->SetMaxPage(9999);

  printer.clear();

  printer.setHorzMgns(leftMargin, rightMargin);   printer.setVertMgns(topMargin, botMargin);

  printer.preparePrinting(font, fontSize, dc, pInfo);

  if (!outputDone) {outputDone = true; onPrepareOutput();}
  }


void  CScrView::trialRun(int& maxLines, int& noPages) {
uint i;

  printer.startDev();   printer.clrLines();

  for (i = 0; !printer.isEndDoc(); i++) {

    if (i) printer.preparePrinting(font, fontSize, dc, info);

    printer.suppressOutput();  printer();   printer.clrFont();
    }

  maxLines = printer.maxLines();    noPages = i;

  if (noPages == 1) maxLines++;  info->m_nCurPage = 1;   preparePrinter(info);
  }


void CScrView::preview(CPrintInfo* pInfo) {
uint i;

  printer.startDev();

  for (i = 1; i < pInfo->m_nCurPage; i++) {

    printer.suppressOutput();   if (!wrapEnabled) printer.disableWrap();

    printer();   printer.clrFont();

    if (!isFinishedPrinting(pInfo)) printer.preparePrinting(font, fontSize, dc, pInfo);
    }
  }


// Draw on Printer (i.e. Output to Printer)

void CScrView::OnPrint(CDC* dc, CPrintInfo* pInfo) {print(pInfo);}


void CScrView::print(CPrintInfo* pInfo) {

  if (!wrapEnabled) printer.disableWrap();   printer();

  startFooter(pInfo, printer.getDisplay());   printer.clrFont();

  if (isFinishedPrinting(pInfo)) {printing = false;  endPrinting = true;}
  }


void CScrView::startFooter(CPrintInfo* pInfo, Display& dev)
                              {dev.setFooter();  printFooter(dev, pInfo->m_nCurPage);   dev.clrFooter();}




void CScrView::printFooter(Display& dev, int pageNo) {          // Overload if different footer desired.

  if (!rightFooter.empty()) dev << rightFooter;

  dev << dCenter << toString(pageNo);

  if (!date.isEmpty()) {dev << dRight; dev << date.getDate() << _T("   ") << date.getTime();}

  dev << dflushFtr;
  }


bool CScrView::isFinishedPrinting(CPrintInfo* pInfo) {
bool fin = printer.isEndDoc();

  pInfo->m_bContinuePrinting = !fin;

  if (fin) {pInfo->SetMaxPage(pInfo->m_nCurPage);}

  return fin;
  }




void CScrView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {printing = false;}


// Display Functions

void CScrView::prepareDisplay() {
  if (printing) return;

  display.clear();

  display.setHorzMgns(leftMargin, rightMargin);   display.setVertMgns(topMargin, botMargin);

  display.prepareDisplay(font, fontSize, dc);   onPrepareOutput();
  }


// CScrView drawing

void CScrView::OnDraw(CDC* pDC)
                              {if (printing) return;   display();   display.clrFont();   setScrollSize();}


//  SB_LINEUP           0
//  SB_LINELEFT         0
//  SB_LINEDOWN         1
//  SB_LINERIGHT        1
//  SB_PAGEUP           2
//  SB_PAGELEFT         2
//  SB_PAGEDOWN         3
//  SB_PAGERIGHT        3
//  SB_THUMBPOSITION    4
//  SB_THUMBTRACK       5
//  SB_TOP              6
//  SB_LEFT             6
//  SB_BOTTOM           7
//  SB_RIGHT            7
//  SB_ENDSCROLL        8


BOOL CScrView::OnScroll(UINT nScrollCode, UINT nPos, BOOL bDoScroll) {
int   x  = nScrollCode >> 8;
POINT pt;
int   nextPos;
int   delta;

  if (x == SB_THUMBTRACK) {

    nextPos = nPos & 0x0000ffff;    pt = GetScrollPosition();

    delta   = nextPos - lastPos;

    if (abs(delta) > 0x6000) {
      if (lastPos > nextPos) delta += 0x10000;
      else                   delta -= 0x10000;
      }
    lastPos = nextPos;  pt.y += delta;  ScrollToPosition(pt); return true;
    }

  return CScrollView::OnScroll(nScrollCode, nPos, bDoScroll);
  }


void CScrView::setScrollSize() {
RECT  winSize;
int   height = display.chHeight();
int   t      = 1;
CSize scrollViewSize;
CSize pageSize;
CSize scrollSize;

  GetClientRect(&winSize);

  if (height) {t = (winSize.bottom - 1) / height; t *= height;}

  pageSize.cy = t; pageSize.cx = winSize.right;

  scrollSize.cx = display.chWidth();   scrollSize.cy = height;

  display.getMaxPos(scrollViewSize.cx, scrollViewSize.cy);

  SetScrollSizes(MM_TEXT, scrollViewSize, pageSize, scrollSize);
  }





