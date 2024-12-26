// Activity Report


#pragma once
#include "ReportBase.h"


class ActvtyRpt : public ReportBase {

CTimeSpan totalTime;

public:

  ActvtyRpt(NotePad& notePad) : ReportBase(notePad, ReportID) { }
 ~ActvtyRpt() { }

 void dspHeader(DevStream& dev) {prtHeader(dev, 1);}
 void dspFooter(DevStream& dev) {prtFooter(dev, 1);}

  void display(CScrView& vw);

  void onPreparePrinting(CPrintInfo* info) {printer.set(prtrOrietn);}
  void onBeginPrinting(CScrView& vw);
                                                  // number of pages that will be produced
  void prtHeader(DevStream& dev, int pageNo);
  void prtFooter(DevStream& dev, int pageNo);          // Output page Footer to NotePad

private:

  ActvtyRpt() : ReportBase(*(NotePad*)0, ReportID) { }

  void getData();
  };

