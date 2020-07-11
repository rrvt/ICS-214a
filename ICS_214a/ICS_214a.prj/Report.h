// Report Output


#pragma once
#include "Display.h"
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

  void trialRun();

  void detWraps();
  void footer(Display& dev, int pageNo);
  void dspFtr();

private:

  void create();

  void header();
  void crlf() {notePad << nCrlf; noLines++;}
  };


extern Report report;
