// Display Device Data


#pragma once
#include "Display.h"
#include "NotePad.h"


class DisplayDev {
Display     dev;

NotePadLoop notePadLp;
Note*       note;

int         lastLeftMargin;

bool        endDoc;
bool        debugging;

public:
uint        lastPageNo;

  DisplayDev() {initialize();}
 ~DisplayDev() { }

  void     preparePrinting(TCchar* font, int fontSize, CDC* pDC, CPrintInfo* pInfo)
                                            {dev.preparePrinting(font, fontSize, pDC, pInfo);}
  void     setNoFooterLns(int n)            {dev.setNoFooterLns(n);}
  void     suppressOutput()                 {dev.suppressOutput();}
  bool     isEndDoc()                       {return endDoc;}
  void     clrFont()                        {dev.clrFont();}

  Display& getDisplay() {return dev;}               // Useful for producing a footer

  // Display functions

  void prepareDisplay( TCchar* font, int fontSize, CDC* pDC) {dev.prepareDisplay(font, fontSize, pDC);}
  int  getWidth()  {return dev.getWidth();}
  int  getHeight() {return dev.getHeight();}
  int  getY()      {return dev.getY();}
  void getMaxPos(long& maxX, long& maxY) {dev.getMaxPos(maxX, maxY);}

  void startDev();
  void operator() ();                  // Output to Device (Display or Printer)

  uint getNoPages()    {return dev.noPages;}

private:

  void initialize();
  };

