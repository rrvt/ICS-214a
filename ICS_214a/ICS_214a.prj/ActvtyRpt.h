// Activity Report


#pragma once
#include "ReportBase.h"


class ActvtyRpt : public ReportBase {

CTimeSpan totalTime;

public:

  ActvtyRpt(NotePad& notePad) : ReportBase(notePad) { }
 ~ActvtyRpt() { }

  void display(CScrView& vw);

  void onPreparePrinting(CPrintInfo* info) {printer.set(prtrOrietn);}
  void onBeginPrinting(CScrView& vw);

  void dspHeader(DevBase& dev) {prtHeader(dev, 1);}
  void dspFooter(DevBase& dev) {prtFooter(dev, 1);}
                                                  // number of pages that will be produced
  void prtHeader(DevBase& dev, int pageNo);
  void prtFooter(DevBase& dev, int pageNo);          // Output page Footer to NotePad

private:

  ActvtyRpt() : ReportBase(*(NotePad*)0) { }

  void getData(CScrView& vw);
  };




//  void detNoPages(CScrView& vw);                  // Performs a dummy printer output to determine the

//  void clearWraps();
//  void detWraps(CScrView& vw);                    // Wrap each entity in the report body
//  int  header(NotePad& np, bool printing);
//  void dspFtr();
//bool      needHdr; , needHdr(false)

