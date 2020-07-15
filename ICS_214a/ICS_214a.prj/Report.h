// Report Output


#pragma once
#include "Display.h"
#include "ICS_214aView.h"
#include "NotePad.h"


class Report {
bool      printing;
int       noLines;
int       maxPages;
int       maxLines;
CTimeSpan totalTime;

public:

  Report() : printing(false), noLines(999), maxPages(0), totalTime(0) { }
 ~Report() { }

  void operator() (bool printing = false);

  void detNoLines(ICS_214aView& vw);
  void detNoPages(ICS_214aView& vw);
  void detWraps(  ICS_214aView& vw);

  void footer(Display& dev, int pageNo);
  void dspFtr();

private:

  void create();

  void header();
  void crlf() {notePad << nCrlf; noLines++;}
  };


extern Report report;
