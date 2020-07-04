// Report Output


#pragma once
#include "Display.h"
#include "NotePad.h"
#include "WrapPrep.h"


class Report {
bool      printing;
int       noLines;
int       maxPages;
CTimeSpan totalTime;

public:

  Report() : printing(false), noLines(999), maxPages(0), totalTime(0) { }
 ~Report() { }

  void operator() (bool printing = false);
  int  detWraps();
  void footer(Display& dev, int pageNo);

private:

  void create();

  void header();
  void crlf() {notePad << nCrlf; noLines++;}
  };


extern Report report;
