// Display to Window
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.


#include "stdafx.h"
#include "Display.h"
#include "EditBoxes.h"
#include "MessageBox.h"


static const long maxScroll = 2147483648;
static const int  Margin    = 3;

static DspManip1& setupManip1(DspManip1::Func fn, int val);


DspManip dClrTabs;    // add to stream to clear tabs: dsp << dClrTabs;
DspManip dCrlf;
DspManip dCR;             // add to stream to perform a carriage return (only)
DspManip dEndPage;    // add to stream to terminate a page when printing or do nothing
DspManip dTab;
DspManip dCenter;
DspManip dRight;      // right align the String following up to the nCrlf
DspManip dBeginLine;
DspManip dEndLine;
DspManip dPrevFont;   // Restore previous font
DspManip dBoldFont;
DspManip dItalicFont;
DspManip dUnderLineFont;
DspManip dStrikeOutFont;
DspManip dflushFtr;   // add to stream to terminate a footer when printing

DspManip1& dSetLMargin(int val) {return setupManip1(Display::doSetLMargin, val);}
DspManip1& dSetTab(    int val) {return setupManip1(Display::doSetTab,     val);}
DspManip1& dSetRTab(   int val) {return setupManip1(Display::doSetRTab,    val);}
DspManip1& dFSize(     int val) {return setupManip1(Display::doFSize,      val);}
DspManip1& dEditBox(   int val) {return setupManip1(Display::doEditBox,    val);}

DspManip1& setupManip1(DspManip1::Func fn, int val)
              {NewAlloc(DspManip1);   DspManip1* m = AllocNode;  new(m) DspManip1(fn, val);  return *m;}




Display::Display()          : tPos(), initialYPos(0),     points{{0,0}} {initialize();}
Display::Display(int initY) : tPos(), initialYPos(initY), points{{0,0}} {initialize();}


void Display::initialize() {

  noPoints = maxHeight = curHeight = toLine = maxY = topEdge = bottomEdge = 0;   y = initialYPos + Margin;
  center = right = beginPage = endPageFlag = false;  footer = false;  noFooterLines = 0; suppress = false;
  dc = 0; tPos.clrTabs();
  points[0] = {0,0};

  printing = false;   noPages = 0;  nonBlankLine = true;

  dCrlf.n           = this; dCrlf.func           = &doCrlf;
  dCR.n             = this; dCR.func             = &doCR;
  dEndPage.n        = this; dEndPage.func        = &doEndPage;
  dflushFtr.n       = this; dflushFtr.func       = &doFlushFtr;
  dTab.n            = this; dTab.func            = &doTab;
  dClrTabs.n        = this; dClrTabs.func        = &doClrTabs;
  dCenter.n         = this; dCenter.func         = &doCenter;
  dRight.n          = this; dRight.func          = &doRight;
  dBeginLine.n      = this; dBeginLine.func      = &doBeginLine;
  dEndLine.n        = this; dEndLine.func        = &doEndLine;

  dPrevFont.n       = this; dPrevFont.func       = &doPrevFont;
  dBoldFont.n       = this; dBoldFont.func       = &doBoldFont;
  dItalicFont.n     = this; dItalicFont.func     = &doItalicFont;
  dUnderLineFont.n  = this; dUnderLineFont.func  = &doUnderLineFont;
  dStrikeOutFont.n  = this; dStrikeOutFont.func  = &doStrikeOutFont;
  }


Display& Display::append(int   v) {String s;   s.format(_T("%li"),  v); sum += s; return *this; }


Display& Display::append(ulong v) {String s;   s.format(_T("%uli"), v);    sum += s; return *this;}


Display& Display::doEditBox(Display& d, int v) {
int curPos = d.tPos.cursorPos;

  d.rightTab = d.tPos.tab();

  editBoxes.create(d.y, v, curPos+1, d.y-2, d.tPos.cursorPos-curPos-1, d.curHeight+1);

  return d;
  }

                                                     // if (y + curHeight >= bottomEdge) setEndPage();


void Display::crlf() {y += maxHeight; maxHeight = curHeight; setMaxY(y);   tPos.doCR();}


Display& Display::doEndPage(Display& d) {

  if (d.printing && d.topEdge < d.y && d.y < d.bottomEdge) {

    if (!d.textOut()) return d;

    d.setEndPage();

    d.tPos.doCR();
    }

  return d;
  }


Display& Display::doFlushFtr(Display& d) {

  d.textOut();

  d.y += d.maxHeight; d.maxHeight = d.curHeight;  d.nonBlankLine = false; d.setMaxY(d.y);

  d.tPos.doCR(); return d;
  }


Display& Display::doBeginLine(Display& d) {
  if (!d.sum.empty() || d.rightTab.right) if (!d.textOut()) return d;

  d.points[0].x = d.tPos.cursorPos; d.points[0].y = d.y + d.toLine; d.noPoints = 1;
  return d;
  }


Display& Display::doEndLine(Display& d) {
  if (!d.sum.empty() || d.center || d.right || d.rightTab.right) if (!d.textOut()) return d;

  d.points[1].x = d.tPos.cursorPos; d.points[1].y = d.y + d.toLine;

  if (d.points[0].y == d.points[1].y && !d.suppress) d.dc->Polyline(d.points, 2);

  LOGPEN logPen;
  CPen*   pen = d.dc->GetCurrentPen(); pen->GetLogPen(&logPen);

  d.noPoints = 0; return d;
  }


void Display::prepareDisplay( TCchar* face, int fontSize, CDC* pDC) {
RECT  winSz;
CWnd* win     = 0;
int   cx      = 0;
int   cy      = 0;

  dc = pDC; printing = false;

  sum.clear(); noPoints = maxHeight = curHeight = 0;   y = initialYPos + Margin;

  tPos.initialize(); center = right = rightTab.right = false; tPos.clrTabs();

  win = pDC->GetWindow(); win->GetClientRect(&winSz);

  cy = winSz.bottom; cx = winSz.right; tPos.iPos(Margin, cx-Margin); setMaxY(y);

  dc->SetMapMode(MM_TEXT);  initializeFont(face, fontSize);
  }


void Display::preparePrinting(TCchar* face, int fontSize, CDC* pDC, CPrintInfo* pInfo) {

  dc = pDC; printing = true;   suppress = false;

  sum.clear(); noPoints = maxHeight = curHeight = y = 0;

  tPos.initialize(); center = right = rightTab.right = false; tPos.clrTabs();

  beginPage = true; endPageFlag = false;

  dc->SetMapMode(MM_TEXT);  initializeFont(face, fontSize);   initializeFrame(pInfo);
  }


void Display::initializeFrame(CPrintInfo* pInfo) {
CPrintDialog* pPD           = 0;                // pointer to print dialog
LPDEVMODE     devMode       = 0;
bool          portrait      = true;
int           h             = 0;
int           w             = 0;
int           yOffset       = 0;
int           xOffset       = 0;
int           cx            = 0;
int           cy            = 0;
int           qtrInch       = 0;
int           sixteenThInch = 0;
int           footerDepth   = printing ? noFooterLines * curHeight : 0;

  if (pInfo) {
    pInfo->m_bContinuePrinting = true;

    pPD = pInfo->m_pPD;
    if (pPD) {
      devMode = pPD->GetDevMode();
      if (devMode && devMode->dmOrientation & DMORIENT_LANDSCAPE) portrait = false;
      }
    }

  cy      = dc->GetDeviceCaps(VERTRES);        cx = dc->GetDeviceCaps(HORZRES);
  h       = dc->GetDeviceCaps(PHYSICALHEIGHT);  w = dc->GetDeviceCaps(PHYSICALWIDTH);

  qtrInch = portrait ? w * 10 / 85 / 4 : w * 10 / 110 / 4;

  sixteenThInch = qtrInch / 4;  yOffset = (h - cy) / 2;   xOffset = (w - cx) / 2;

  xOffset = qtrInch + sixteenThInch - xOffset;

  topEdge = qtrInch + sixteenThInch - yOffset;                              // + sixteenThInch;

  bottomEdge = cy - topEdge - 3*sixteenThInch - footerDepth;

  y = initialYPos ? initialYPos : topEdge;

  tPos.iPos(xOffset, cx - xOffset);
  }


void Display::initializeFont(TCchar* face, int fontSize)
                                 {font.initialize(face, fontSize, dc); setMetric();}
void Display::setFontSize(int v) {if (textOut()) {font.setSize(v);     setMetric();}}
void Display::boldFont()         {if (textOut()) {font.setBold();      setMetric();}}
void Display::italicFont()       {if (textOut()) {font.setItalic();    setMetric();}}
void Display::underLineFont()    {if (textOut()) {font.setUnderLine(); setMetric();}}
void Display::strikeOutFont()    {if (textOut()) {font.setStrikeOut(); setMetric();}}
void Display::prevFont()         {if (textOut()) {font.pop();          setMetric();}}


void Display::setMetric() {
TEXTMETRIC metric;
int        buf[26];
int        i;
double     sum;
double     avg;
int        chWidth;

  if (dc->GetTextMetrics(&metric)) {

    dc->GetCharWidth(_T('A'), _T('Z'), buf);
    for (i = 0, sum = 0; i < noElements(buf); i++) sum += buf[i];
    avg = sum / noElements(buf) + 0.5;   chWidth = (int) avg;

    if (metric.tmAveCharWidth > chWidth) chWidth = metric.tmAveCharWidth;

    curHeight = metric.tmHeight + metric.tmExternalLeading + 2;

    if (!tPos.getCharPos() || curHeight > maxHeight) maxHeight = curHeight;

    toLine = curHeight - metric.tmInternalLeading - metric.tmExternalLeading;

    if (chWidth > tPos.width) tPos.width = chWidth;    tPos.lastWidth = chWidth;
    }
  }



bool Display::textOut() {
int  wth = width(sum);
Wrap wrap;
int  n;
int  i;
int  curPos;
int  nLines;

  if (center) {        tPos.centerPos(wth);             center         = false;}
  if (right)          {tPos.rightPos(wth);              right          = false;}
  if (rightTab.right) {tPos.rightTabPos(rightTab, wth); rightTab.right = false;}

  if (sum.empty()) return true;

  if (beginPage) {noPages++; beginPage = false;}

  if (endPageFlag) {endPageFlag = false; beginPage = true;}

  wrap.initialize(dc, tPos.remaining() + (printing ? tPos.widthCh() : 0), font.getAttr()->italic);
  nLines = wrap(sum);

  if (!footer && printing && y + curHeight * nLines >= bottomEdge) {setEndPage(); return false;}

  n = wrap.lines.end();   curPos = tPos.get();

  if (footer && y < bottomEdge) y = bottomEdge;

  for (i = 0; i < n; i++) {
    if (i) {crlf(); tPos.pos(curPos);}

    fragmentOut(wrap.lines[i]);
    }

  sum.clear();  return true;
  }


void Display::fragmentOut(String& frag) {
CString cs;  cs = frag;

  if (!suppress) {

    try {if (!dc->TextOut(tPos.cursorPos, y, cs)) {outError(cs); return;}}
    catch (...)                                   {outError(cs); return;}
    }

  tPos.move(width(frag));
  }



// returns CString and width in current units

int Display::width(String& s) {
CString cs;
CSize   sz;
bool    italic = font.getAttr()->italic;

  cs = s;   sz = dc->GetOutputTextExtent(cs);

  return italic ? sz.cx + 2 : sz.cx;
  }



void Display::outError(TCchar* stg) {
String err = _T("Unable to output: '"); err += stg; err += _T("'");

  messageBox(err);
  }







