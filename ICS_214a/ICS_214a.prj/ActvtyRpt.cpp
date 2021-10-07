// Activity Report


#include "stdafx.h"
#include "ActvtyRpt.h"
#include "Activity.h"
#include "CScrView.h"


void ActvtyRpt::display(CScrView& vw)
                 {printing = false; vw.disableWrap(false); detWraps(vw); maxLines = BigNmbr; create(vw);}


void ActvtyRpt::print(CScrView& vw) {

  printing = true;   vw.disableWrap(printing);   maxLines = vw.noLinesPrPg();

  vw.enableWrap(printing);   detWraps(vw);   detNoPages(vw);

  create(vw);
  }



void ActvtyRpt::detWraps(CScrView& vw) {
Device&   dev = vw.getDev(printing);
CDC*      dc  = dev.getDC();
ActyIter  iter(activity);
LogData*  ld;

  for (ld = iter(); ld; ld = iter++)
    ld->wrap(dev, dc);
  }


void ActvtyRpt::create(CScrView& vw) {
ActyIter iter(activity);
LogData* ld;
LONGLONG secs;
double   ttl;
int      i;
String   t;
int      n;

  if (!iter()) return;

  np.clear();   totalTime = 0;    noLines = BigNmbr;

  for (i = 0, ld = iter(); ld; i++, ld = iter++) {

    n = ld->noLines();

    if (iter.isLast()) n += 2;

    if (noLines + n > maxLines) {
      if (i) np << nEndPage;    noLines = header(np, printing);
      }

    totalTime += ld->display(noLines, np);
    }

  secs = totalTime.GetTotalSeconds();   ttl = (double) secs / 3600.0;   t.format(_T("%0.2f"), ttl);
  np << nCrlf; noLines++;
  np << _T("   Total Time:") << nTab << t << nTab << _T("hours") << nCrlf; noLines++;

  if (!printing) dspFtr();
  }


int ActvtyRpt::header(NotePad& np, bool printing) {

  np << nClrTabs << nSetTab(18) << nSetRTab(45);

  np << nBold << nFSize(16.0) << _T("ICS 214a Unit Log") << nFont << nFont;
  np << nTab << nFSize(9.0) << _T("1. Incident Name");
  np << nRight << _T("2. Date and 3. Time Prepared") << nFont;   np << nCrlf;

  np << nBold << _T("SJ RACES") << nFont;
  np << nTab << activity.name;
  np << nRight << activity.prepDate << _T(" - ") <<  activity.prepTime;
  np << nCrlf << nCrlf;

  np << nClrTabs << nSetTab(14) << nSetRTab(55);

  np << nFSize(9.0) << _T("4. Unit Name Designator") << nTab;
  np << _T("5. Unit Leader: (Name and Position)") << nRight;
  np << _T("6. Operational Period") << nFont;   np << nCrlf;

  np << _T("San Jose RACES");
  np << nTab << activity.leaderName << _T(" ") << activity.leaderPosition;
  np << nRight << activity.operationalPeriod;   np << nCrlf << nCrlf;

  np << nClrTabs << nSetTab(6) << nSetRTab(17) << nSetTab(18);
  np << nFSize(9.0) << _T("Date") << nTab << _T("Start Time") << nTab << _T("End Time");
  np << nTab << _T("Activity") << nFont;   np << nCrlf; return 7;
  }


void ActvtyRpt::footer(Device& dev, int pageN) {
#if 0
  if (pageN > maxPages) maxPages = pageN;

  dev << dRight << pageN << _T(" of ") << maxPages << dflushFtr;
#endif

  if (pageN > maxPages) maxPages = pageN;

  dev << dClrTabs << dSetTab(7);
  dev << dFSize(9.0) << _T("ICS 214a") << dTab << _T("8. Prepared By") << dCenter;
  dev << _T("9. Mission Number") << dRight << _T("10. Page No.")  << dPrevFont << dCrlf;

  dev << _T("RACES") << dTab << activity.preparedBy << dCenter << activity.missionNo;
  dev << dRight << pageN << _T(" of ") << maxPages << dFlushFtr;
  }



void ActvtyRpt::dspFtr() {

  np << nCrlf;

  np << nClrTabs << nSetTab(7);
  np << nFSize(9.0) << _T("ICS 214a") << nTab << _T("8. Prepared By") << nCenter;
  np << _T("9. Mission Number") << nRight << _T("10. Page No.")  << nFont << nCrlf;

  np << _T("RACES") << nTab << activity.preparedBy << nCenter << activity.missionNo;
  np << nRight << _T("1") << _T(" of ") << _T("1") << nCrlf;
  }




#if 0
DSIter iter(store);
Data*  datum;
int    i;

  np.clear();   noLines = BigNmbr;

  for (i = 0, datum = iter(); datum; i++, datum = iter++) {

    if (noLines + 1 > maxLines) {

      if (i) np << nEndPage;

      header();  np << nClrTabs << nSetTab(10);
      }

    np << datum->get() << nCrlf;   noLines += 1;
    }
#endif

