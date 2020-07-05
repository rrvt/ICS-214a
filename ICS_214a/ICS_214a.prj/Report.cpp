// Report Output


#include "stdafx.h"
#include "Report.h"
#include "Activity.h"
#include "ICS_214a.h"
#include "ICS_214aView.h"
#include "Utilities.h"


static const int linesPerPg  = 52;
static const int opPeriodTab = 50;

Report report;


void Report::operator() (bool printing) {

  this->printing = printing;

  maxPages = detWraps();

  create();
  }


int Report::detWraps() {
ICS_214aView& vw  = *view();
Display&      dev = vw.getDev();
ActivityIter  iter(activity);
LogData*      ld;
int           noHeaderLns;
int           noLines;
int           noPages = 0;
int           n;
CDC*          dc = dev.getDC();

  noHeaderLns = 7 + activity.wrapOpPer(opPeriodTab, dev, dc);   noLines = noHeaderLns;

  for (ld = iter(); ld; ld = iter++) {
    n = ld->wrap(dev, dc);    if (iter.last()) n += 2;

    if (n + noLines >= linesPerPg) {noPages++; noLines = noHeaderLns;}

    noLines += n;
    }

  if (noLines) noPages++;

  return noPages;
  }


void Report::create() {
ActivityIter iter(activity);
LogData*     ld;
LONGLONG     secs;
double       ttl;
String       t;
int          n;
bool         endPage = false;

  if (!iter()) return;

  notePad.clear();   totalTime = 0;    header();

  for (ld = iter(); ld; ld = iter++) {

    n = ld->noLines();  if (iter.last()) n += 2;

    endPage = printing && n + noLines >= linesPerPg;

    if (endPage) {notePad << nEndPage;    header();}

    totalTime += ld->display(noLines);
    }

  secs = totalTime.GetTotalSeconds();   ttl = (double) secs / 3600.0;   t.format(_T("%0.2f"), ttl);
  crlf();    notePad << _T("   Total Time:") << nTab << t << nTab << _T("hours");   crlf();

  if (printing) notePad << nEndPage;
  }




void Report::header() {

  noLines = 0;

  notePad << nClrTabs << nSetTab(18) << nSetTab(53) << nSetRTab(70);

  notePad << nBold << nFSize(160) << _T("ICS 214a Unit Log") << nFont << nFont;
  notePad << nTab << nFSize(90) << _T("Incident Name") << nTab << _T("Date Prepared");
  notePad << nTab << _T("Time Prepared") << nFont;   crlf();

  notePad << nBold << _T("SJ RACES") << nFont;
  notePad << nTab << activity.name;
  notePad << nTab << activity.prepDate;
  notePad << nTab << activity.prepTime;   crlf();   crlf();

  notePad << nClrTabs << nSetTab(14) << nSetTab(32) << nSetRTab(70);

  notePad << nFSize(90) << _T("Unit Name Designator") << nTab << _T("Unit Leader: Name");
  notePad << nTab << _T("Position") << nTab << _T("Operational Period") << nFont;   crlf();
  notePad << _T("San Jose RACES");
  notePad << nTab << activity.leaderName;
  notePad << nTab << activity.leaderPosition << nTab << activity.operationalPeriod;
//  noLines += activity.dspOpPer();
  crlf(); crlf();

  notePad << nClrTabs << nSetTab(6) << nSetRTab(17) << nSetTab(18);
  notePad << nFSize(90) << _T("Date") << nTab << _T("Start Time") << nTab << _T("End Time");
  notePad << nTab << _T("Activity") << nFont;   crlf();
  }


void Report::footer(Display& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dClrTabs << dSetTab(7) << dSetRTab(70);
  dev << dFSize(90) << _T("ICS 214a") << dTab << _T("Prepared By") << dCenter;
  dev << _T("Mission Number") << dTab << _T("Page No.")  << dPrevFont << dCrlf;

  dev << dClrTabs << dSetTab(7) << dSetRTab(70);
  dev << _T("RACES") << dTab << activity.preparedBy << dCenter << activity.missionNo;
  dev << dTab << pageN << _T(" of ") << maxPages << dflushFtr;
  }

