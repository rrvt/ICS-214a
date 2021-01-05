// Activity Report


#pragma once
#include "ReportBase.h"


class ActvtyRpt : public ReportBase {

CTimeSpan totalTime;

public:

  ActvtyRpt(NotePad& notePad) : ReportBase(notePad) { }
 ~ActvtyRpt() { }

  void ActvtyRpt::display(CScrView& vw);
  void print(CScrView& vw);

//  void detWraps(  CScrView& vw);               // Wrap each entity in the report body
  void detWraps(  CScrView& vw);

//  void detNoPages(CScrView& vw);               // Performs a dummy printer output to determine the
                                                  // number of pages that will be produced
  void footer(Device& dev, int pageNo);          // Output page Footer to NotePad
  void dspFtr();

private:

  ActvtyRpt() : ReportBase(*(NotePad*)0) { }

  void create();
  int  header(NotePad& np, bool printing);
  };

