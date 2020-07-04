// Display to Window
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.

#pragma once

#include "FontMgr.h"
#include "ManipT.h"
#include "TextPosition.h"
#include "Wrap.h"


class Display;


typedef ManipT<   Display> DspManip;
typedef ManipValT<Display> DspManip1;


class Display {
CDC*         dc;
TextPosition tPos;
FontMgr      font;

String       sum;
int          noPoints;
POINT        points[20];
int          curHeight;                     // Text height
int          maxHeight;                     // Max text height to deal with font changes
int          toLine;                        // Distance to Line
const int    initialYPos;                   // Initial vertical position in pixels from the top of window
int          y;                             // Vertical position in pixels from top of window
int          maxY;
int          topEdge;                       // pixels from top edge of screen/printer
int          bottomEdge;                    // pixels of bottom edge from printable top edge
bool         nonBlankLine;                  // true when first non blank line is encountered during
                                            // printing

bool         center;                        // center string in window when true;
bool         right;                         // right align in window when true;
Tab          rightTab;                      // right align to tab value when true;
bool         beginPage;
bool         endPageFlag;                   // Signal the end of a page

bool         footer;
int          noFooterLines;

public:

bool         printing;                      // Printing when true, else displaying
bool         suppress;
uint         noPages;

  Display();
  Display(int initY);
 ~Display() {}

  void     prepareDisplay( TCchar* face, int fontSize, CDC* pDC);
  void     preparePrinting(TCchar* face, int fontSize, CDC* pDC, CPrintInfo* pInfo);
  void     setNoFooterLns(int n) {noFooterLines = n;}
  void     suppressOutput() {suppress = true;}
  void     setFooter() {footer = true;}

  Display& operator<< (String&    s) {return stg(s);}
  Display& operator<< (TCchar*    s) {return stg(s);}
  Display& operator<< (int        v) {return append(v);}
  Display& operator<< (ulong      v) {return append(v);}
  Display& operator<< (DspManip&  m) {return m.func(*this);}
  Display& operator<< (DspManip1& m) {m.func(*this, m.v); NewAlloc(DspManip1); FreeNode(&m); return *this;}

  CDC*     getDC() {return dc;}
  int      remaining() {return tPos.remaining();}

  FontAttr&     getCurFont() {return font.current;}
  LOGFONT&      getLogFont() {return font.getLogFont();}
  TextPosition& getTextPos() {return tPos;}

private:
         void     initializeFrame(CPrintInfo* pInfo);

         void     clrFont()                         {font.pop();}
         void     resetMaxY()                       {maxY = 0;}
         void     getMaxPos(long& maxX, long& maxY) {maxX = tPos.maxCursorPos; maxY = this->maxY;}
         bool     withinBounds()                    {return topEdge < y && y < bottomEdge;}
         bool     isEndPage()                       {return printing && endPageFlag && y > topEdge;}
         int      getWidth()                        {return tPos.width;}
         int      getRemainder()                    {return tPos.remaining();}
         int      getHeight()                       {return curHeight;}
         int      getY()                            {return y;}

  static Display& doClrTabs(       Display& d) {d.tPos.clrTabs(); return d;}
  static Display& doCrlf(          Display& d)
                                            {if (d.textOut() && d.nonBlankLine) {d.crlf();}  return d;}
  static Display& doCR(            Display& d) {if (d.textOut()) d.tPos.doCR(); return d;}

  static Display& doEndPage(       Display& d);
  static Display& doTab(           Display& d) {if (d.textOut()) d.rightTab = d.tPos.tab();  return d;}

  static Display& doCenter(        Display& d) {if (d.textOut())  d.center = true;  return d;}
  static Display& doRight(         Display& d) {if (d.textOut())  d.right  = true;  return d;}
  static Display& doBeginLine(     Display& d);
  static Display& doEndLine(       Display& d);

  static Display& doBoldFont(      Display& d) {d.boldFont();      return d;}
  static Display& doItalicFont(    Display& d) {d.italicFont();    return d;}
  static Display& doUnderLineFont( Display& d) {d.underLineFont(); return d;}
  static Display& doStrikeOutFont( Display& d) {d.strikeOutFont(); return d;}
  static Display& doPrevFont(      Display& d) {d.prevFont();      return d;}

  static Display& doFlushFtr(      Display& d);

  static Display& doSetTab(        Display& d, int v) {d.tPos.setTab(v);  return d;}
  static Display& doSetRTab(       Display& d, int v) {d.tPos.setRTab(v); return d;}
  static Display& doSetLMargin(    Display& d, int v) {d.tPos.setLeftMargin(v); return d;}
  static Display& doEditBox(       Display& d, int v);
  static Display& doFSize(         Display& d, int v) {d.setFontSize(v);  return d;}


  void     initialize();
  Display& stg(TCchar*  s) {if (*s) nonBlankLine = true;   sum += s; return *this;}
  Display& stg(String&  s) {return this->stg(s.str());}
  Display& append(int   v);
  Display& append(ulong v);

  int      getMaxVertPos() {return y;}

  void     setMaxY(int t) {if (t > maxY) maxY = t;}
  void     setLMargin(int lm) {tPos.setLeftMargin(lm);}

  void     crlf();

  void     initializeFont(TCchar* face, int fontSize);
  void     setFontSize(int v);
  void     boldFont();
  void     prevFont();
  void     italicFont();
  void     underLineFont();
  void     strikeOutFont();
  void     setPrevFont();
  void     setMetric();

  bool     textOut();                                 // fails when end of page and printing
  void     fragmentOut(String& s);
  int      width(String& s);          // returns CString and width in current units
  void     outError(TCchar* stg);
  void     setEndPage() {if (printing) {y = bottomEdge; endPageFlag = true;} }

  friend DspManip1& dSetLMargin(int val);
  friend DspManip1& dSetTab(    int val);
  friend DspManip1& dSetRTab(   int val);
  friend DspManip1& dFSize(     int val);
  friend DspManip1& dEditBox(   int val);
  friend class DisplayDev;
  };


// No Argument Manipulator

extern DspManip dClrTabs;        // add to stream to clear tabs:                   dsp << dClrTabs;
extern DspManip dCrlf;           // add to stream to terminate a line on display:  dsp << "xyz" << dCrlf;
extern DspManip dCR;             // add to stream to perform a carriage return (only)
extern DspManip dEndPage;        // add to stream to terminate a page when printing or do nothing
extern DspManip dflushFtr;       // add to stream to terminate a footer when printing
extern DspManip dTab;            // add to stream to tab to next tab position:     dsp << dTab << "xyz";
extern DspManip dCenter;         // center the string following up to the nCrlf
extern DspManip dRight;          // right align the string following up to the nCrlf
extern DspManip dBeginLine;      // begin line here
extern DspManip dEndLine;        // end line here -- Does not affect current position
extern DspManip dPrevFont;       // Restore previous font
extern DspManip dBoldFont;
extern DspManip dItalicFont;
extern DspManip dUnderLineFont;
extern DspManip dStrikeOutFont;

// One Argument Manipulator

// insert in stream dsp << dSetTab(n) << ... where n is ~no of characters from margin, etc.

DspManip1& dSetLMargin(int val);
DspManip1& dSetTab(    int val);
DspManip1& dSetRTab(   int val);
DspManip1& dFSize(     int val);
DspManip1& dEditBox(   int val);


