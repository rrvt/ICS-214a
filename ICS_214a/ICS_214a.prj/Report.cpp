// Report Output


#include "stdafx.h"
#include "Report.h"
#include "Activity.h"
#include "ICS_214a.h"
#include "Utilities.h"


Report report;


void Report::operator() (bool printing) {
ICS_214aView& vw  = *view();

  this->printing = printing;

  if (printing) detNoLines(vw);

  detWraps(vw);

  vw.disableWrap();

  if (printing) detNoPages(vw);

//  vw.disableWrap();

  create();
  }


void Report::detNoLines(ICS_214aView& vw) {
int i;
int mxPgs;

  vw.suppressOutput();   maxLines = 999999;

  notePad.clear();

  // Header simulation
  notePad << nBold << nFSize(160) << _T("ICS 214a Unit Log") << nFont << nFont << nCrlf;
  notePad << nBold << _T("SJ RACES") << nFont << nCrlf << nCrlf;
  notePad << nFSize(90) << _T("4. Unit Name Designator") << nFont << nCrlf;
  notePad << _T("San Jose RACES") << nCrlf << nCrlf;
  notePad << nFSize(90) << _T("Date") << nFont << nCrlf;

  for (i = 8; i < 65; i++) {
    String s; s.format(_T("Line %i"), i);
    notePad  << s << nCrlf;
    }

  vw.trialRun(maxLines, mxPgs);
  }


void Report::detWraps(ICS_214aView& vw) {
Display&  dev = vw.getDev();
CDC*      dc  = dev.getDC();
ActyIter  iter(activity);
LogData*  ld;

  for (ld = iter(); ld; ld = iter++) ld->wrap(dev, dc);
  }


void Report::detNoPages(ICS_214aView& vw) {int nLns;   create();   vw.trialRun(nLns, maxPages);}


void Report::create() {
ActyIter iter(activity);
LogData* ld;
LONGLONG secs;
double   ttl;
String   t;
int      n;

  if (!iter()) return;

  notePad.clear();   totalTime = 0;    header();

  for (ld = iter(); ld; ld = iter++) {

    n = ld->noLines();

    if (iter.isLast()) n += 2;

    if (printing && n + noLines > maxLines)
      {notePad << nEndPage;    header();}

    totalTime += ld->display(noLines);
    }

  secs = totalTime.GetTotalSeconds();   ttl = (double) secs / 3600.0;   t.format(_T("%0.2f"), ttl);
  crlf();    notePad << _T("   Total Time:") << nTab << t << nTab << _T("hours");   crlf();

  if (printing) notePad << nEndPage;
  else          dspFtr();
  }




void Report::header() {

  noLines = 0;

  notePad << nClrTabs << nSetTab(18) << nSetRTab(45);

  notePad << nBold << nFSize(160) << _T("ICS 214a Unit Log") << nFont << nFont;
  notePad << nTab << nFSize(90) << _T("1. Incident Name");
  notePad << nRight << _T("2. Date and 3. Time Prepared") << nFont;   crlf();

  notePad << nBold << _T("SJ RACES") << nFont;
  notePad << nTab << activity.name;
  notePad << nRight << activity.prepDate << _T(" - ") <<  activity.prepTime;
  crlf();   crlf();

  notePad << nClrTabs << nSetTab(14) << nSetRTab(55);

  notePad << nFSize(90) << _T("4. Unit Name Designator") << nTab;
  notePad << _T("5. Unit Leader: (Name and Position)") << nRight;
  notePad << _T("6. Operational Period") << nFont;   crlf();

  notePad << _T("San Jose RACES");
  notePad << nTab << activity.leaderName << _T(" ") << activity.leaderPosition;
  notePad << nRight << activity.operationalPeriod;   crlf(); crlf();

  notePad << nClrTabs << nSetTab(6) << nSetRTab(17) << nSetTab(18);
  notePad << nFSize(90) << _T("Date") << nTab << _T("Start Time") << nTab << _T("End Time");
  notePad << nTab << _T("Activity") << nFont;   crlf();
  }


void Report::footer(Display& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dClrTabs << dSetTab(7);
  dev << dFSize(90) << _T("ICS 214a") << dTab << _T("8. Prepared By") << dCenter;
  dev << _T("9. Mission Number") << dRight << _T("10. Page No.")  << dPrevFont << dCrlf;

  dev << _T("RACES") << dTab << activity.preparedBy << dCenter << activity.missionNo;
  dev << dRight << pageN << _T(" of ") << maxPages << dflushFtr;
  }


void Report::dspFtr() {

  notePad << nCrlf;

  notePad << nClrTabs << nSetTab(7);
  notePad << nFSize(90) << _T("ICS 214a") << nTab << _T("8. Prepared By") << nCenter;
  notePad << _T("9. Mission Number") << nRight << _T("10. Page No.")  << nFont << nCrlf;

  notePad << _T("RACES") << nTab << activity.preparedBy << nCenter << activity.missionNo;
  notePad << nRight << _T("1") << _T(" of ") << _T("1") << nCrlf;
  }

