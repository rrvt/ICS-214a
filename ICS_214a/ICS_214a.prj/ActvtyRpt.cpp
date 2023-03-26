// Activity Report


#include "stdafx.h"
#include "ActvtyRpt.h"
#include "Activity.h"
#include "CScrView.h"


void ActvtyRpt::display(CScrView& vw) {printing = false;   vw.enableDplWrap();     getData(vw);}


void ActvtyRpt::onBeginPrinting(CScrView& vw) {printing = true;   vw.enablePrtWrap();   getPageAttr(vw);}


void ActvtyRpt::getData(CScrView& vw) {
ActyIter iter(activity);
Event*   event;
LONGLONG secs;
double   ttl;
int      i;
String   t;

  if (!iter()) return;

  np.clear();   totalTime = 0;

  for (i = 0, event = iter(); event; i++, event = iter++) totalTime += event->display(np);

  secs = totalTime.GetTotalSeconds();   ttl = (double) secs / 3600.0;   t.format(_T("%0.2f"), ttl);
  np << nCrlf;
  np << _T("   Total Time:") << nTab << t << nTab << _T("hours") << nCrlf;
  }



void ActvtyRpt::prtHeader(DevBase& dev, int pageNo) {

  dev << dClrTabs << dSetTab(18) << dSetRTab(45);

  dev << dBold << dFSize(16.0) << _T("ICS 214a Unit Log") << dFont << dFont;
  dev << dTab << dFSize(9.0) << _T("1. Incident Name");
  dev << dRight << _T("2. Date and 3. Time Prepared") << dFont;   dev << dCrlf;

  dev << dBold  << _T("SJ RACES") << dFont;
  dev << dTab   << activity.name;
  dev << dRight << activity.prepDate << _T(" ") <<  activity.prepTime;
  dev << dCrlf  << dCrlf;

  dev << dClrTabs << dSetTab(14) << dSetRTab(55);

  dev << dFSize(9.0) << _T("4. Unit Name Designator");
  dev << dTab        << _T("5. Unit Leader: (Name and Position)");
  dev << dRight      << _T("6. Operational Period") << dFont << dCrlf;

  dev << _T("San Jose RACES");
  dev << dTab   << activity.leaderName << _T(" ") << activity.leaderPosition;
  dev << dRight << activity.operationalPeriod << dCrlf << dCrlf;

  dev << dClrTabs << dSetTab(6) << dSetRTab(17) << dSetTab(18);

  dev << dFSize(9.0) << _T("Date") << dTab << _T("Start Time") << dTab << _T("End Time");
  dev << dTab << _T("Activity") << dFont << dCrlf;
  }


void ActvtyRpt::prtFooter(DevBase& dev, int pageN) {

  if (pageN > maxPages) maxPages = pageN;

  dev << dClrTabs << dSetTab(7);
  dev << dFSize(9.0) << _T("ICS 214a") << dTab << _T("8. Prepared By") << dCenter;
  dev << _T("9. Mission Number") << dRight << _T("10. Page No.")  << dFont << dCrlf;

  dev << _T("RACES") << dTab << activity.preparedBy << dCenter << activity.missionNo;
  dev << dRight << pageN << _T(" of ") << maxPages << dFlushFtr;
  }




