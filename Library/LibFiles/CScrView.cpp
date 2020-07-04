// Scroll View


#include "stdafx.h"
#include "CScrView.h"
#include "NotePad.h"


int CScrView::lastPos = 0;


BEGIN_MESSAGE_MAP(CScrView, CScrollView)
  ON_COMMAND(ID_FILE_PRINT,         &CScrView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_DIRECT,  &CScrollView::OnFilePrint)
  ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrView::OnFilePrintPreview)
END_MESSAGE_MAP()


// Default Print starting logic, it is virtual so it can be replaced with out removing this code...

void CScrView::OnFilePrint() {printer.setNoFooterLns(noFooterLines);  CScrollView::OnFilePrint();}
void CScrView::OnFilePrintPreview()
                             {printer.setNoFooterLns(noFooterLines);  CScrollView::OnFilePrintPreview();}


BOOL CScrView::PreCreateWindow(CREATESTRUCT& cs) {return CScrollView::PreCreateWindow(cs);}



void CScrView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
                                        {setScrollSize(); CScrollView::OnUpdate(pSender, lHint, pHint);}


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

BOOL CScrView::OnPreparePrinting(CPrintInfo* pInfo)
  {printing = true; prtPage = 0; return DoPreparePrinting(pInfo);}
                                                                              // Get printer dialog box

void CScrView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {

  if (printing && !pInfo) return;

  dc = pDC;   CScrollView::OnPrepareDC(dc, pInfo);    printing = dc->IsPrinting();

  if (printing) preparePrinter(pInfo);
  else          prepareDisplay();

  if (printing && pInfo->m_bPreview) preview(pInfo);
  }



void CScrView::onPrepareOutput() {

  if (!printing) {display.startDev(); return;}

  if (!endPrinting) printer.startDev();
  }


void CScrView::preparePrinter(CPrintInfo* pInfo) {
int pageNo = pInfo->m_nCurPage;

  pInfo->m_bContinuePrinting = true;     endPrinting = false;

  pInfo->m_nNumPreviewPages = 0;

  pInfo->SetMinPage(1);   pInfo->SetMaxPage(9999);    //printer.startDev();

  printer.preparePrinting(font, fontSize, dc, pInfo);

  if (pageNo == 1 && pageNo != prtPage) onPrepareOutput();
  }


void CScrView::preview(CPrintInfo* pInfo) {
uint i;

  if (pInfo->m_nCurPage > prtPage) return;

  printer.startDev();

  for (i = 1; i < pInfo->m_nCurPage; i++) {

    printer.suppressOutput();   printer();   printer.clrFont();

    if (!isFinishedPrinting(pInfo)) printer.preparePrinting(font, fontSize, dc, pInfo);
    }
  }


// Draw on Printer (i.e. Output to Printer)

void CScrView::OnPrint(CDC* dc, CPrintInfo* pInfo) {print(pInfo);}


void CScrView::print(CPrintInfo* pInfo) {

  printer();  startFooter(pInfo);   prtPage = pInfo->m_nCurPage;

  printer.clrFont();

  if (isFinishedPrinting(pInfo)) {printing = false;  endPrinting = true;}
  }


void CScrView::startFooter(CPrintInfo* pInfo) {
Display footer(printer.getY());

  footer.preparePrinting(font, fontSize, dc, pInfo);   footer.setFooter();

  printFooter(footer, pInfo->m_nCurPage);
  }




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
                                                                //if (!pInfo->m_bPreview) invalidate();

// Display Functions

void CScrView::prepareDisplay() {display.prepareDisplay(font, fontSize, dc);  onPrepareOutput();}


// CScrView drawing

void CScrView::OnDraw(CDC* pDC) {display();   display.clrFont();   setScrollSize();}


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
int        x  = nScrollCode >> 8;
POINT      pt;
int        nextPos;
int        delta;

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
int   height = display.getHeight();
int   t      = 1;
CSize scrollViewSize;
CSize pageSize;
CSize scrollSize;

  GetClientRect(&winSize);

  if (height) {t = (winSize.bottom - 1) / height; t *= height;}

  pageSize.cy = t; pageSize.cx = winSize.right;

  scrollSize.cx = display.getWidth();   scrollSize.cy = height;

  display.getMaxPos(scrollViewSize.cx, scrollViewSize.cy);

  SetScrollSizes(MM_TEXT, scrollViewSize, pageSize, scrollSize);
  }




