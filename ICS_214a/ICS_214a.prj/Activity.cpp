// ICS-214a -- Activity Log


#include "stdafx.h"
#include "Activity.h"
#include "Options.h"
#include "Utilities.h"


Activity activity;



void Activity::clear() {
  storeType = NilStore;
  log.clr();

  name.clear();
  prepDate.clear();
  prepTime.clear();
  leaderName.clear();
  leaderPosition.clear();
  operationalPeriod.clear();
  preparedBy.clear();
  missionNo.clear();
  }



void Activity::add(TCchar* date, TCchar* timeIn, TCchar* timeOut, TCchar* desc) {
LogData& data = log[log.end()];

  data.set(date, timeIn, 0, timeOut, desc);
  }


void Activity::load(Archive&  ar) {
CSVrecord rcd(ar);

  if (!loadHeader(rcd)) return;
  loadLog(rcd);
  }


bool Activity::loadHeader(CSVrecord& rcd) {
CSVfield* fld;
int       i;

  if (!rcd.load()) return false;

  for (fld = rcd.startLoop(), i = 0; fld; fld = rcd.nextFld(), i++) {

    fld->name.trim();

    switch (i) {
      case 0: name              = fld->name; break;
      case 1: prepDate          = fld->name; break;
      case 2: prepTime          = fld->name; break;
      case 3: leaderName        = fld->name; break;
      case 4: leaderPosition    = fld->name; break;
      case 5: operationalPeriod = fld->name; break;
      case 6: preparedBy        = fld->name; break;
      case 7: missionNo         = fld->name; break;
      }
    }
  return true;
  }


void Activity::loadLog(CSVrecord& rcd) {
int i;

  log.clr();

  for (i = 0; rcd.load(); i++) log[log.end()].load(rcd);

  }



void LogData::load(CSVrecord& rcd) {
int       i;
CSVfield* fld;

  for (fld = rcd.startLoop(), i = 0; fld; fld = rcd.nextFld(), i++) {

    fld->name.trim();

    switch (i) {
      case 0: date    = fld->name; break;
      case 1: timeIn  = fld->name; break;
      case 2: dateOut = fld->name; if (dateOut == date) dateOut.clear();   break;
      case 3: timeOut = fld->name; break;
      case 4: desc    = fld->name; break;
      }
    }

  setDeltaT();  archived = true;
  }


void Activity::store(Archive& ar) {
  switch (storeType) {
    case StoreIncr  : storeIncr(ar);  break;
    case StoreAll   : storeAll(ar);   break;
    case StoreExcel : storeExcel(ar); break;
    }
  }


void Activity::storeIncr(Archive&  ar) {storeIncrLogData(ar);}


void Activity::storeAll(Archive&  ar) {storeHeader(ar);   storeLogData(ar);}


/*
ICS 214a  Unit Log    Date Prepared 7/4/2020
Ver: NC     Time Prepared 0:00
      Incident Name forVerification
      Operational Period  7/4/2020_0600 to 7/5/2020_0600
      Unit Name Designator
      Unit Leader: Name Lowell Papa
      Position  Field Operator


ICS 214a,Unit Log,,Date Prepared,7/4/2020
Ver: NC,,,Time Prepared,0:00
,,,Incident Name,forVerification
,,,Operational Period,7/4/2020_0600 to 7/5/2020_0600
,,,Unit Name Designator,
,,,Unit Leader: Name,Lowell Papa
,,,Position,Field Operator
*/

void Activity::storeExcel(Archive&  ar) {
CSVout co(ar);

  if (options.excelOne) {
    co << _T("ICS 214a") << _T(',') << _T("Unit Log") << _T(',') << _T(',') << _T("Date Prepared");
    co << _T(',') << prepDate << vCrlf;

    co << _T("Ver: NC") << _T(',') << _T(',') << _T(',') << _T("Time Prepared");
    co << _T(',') << prepTime << vCrlf;

    co << _T(',') << _T(',') << _T(',') << _T("Incident Name") << _T(',') << name << vCrlf;
    co << _T(',') << _T(',') << _T(',') << _T("Operational Period") << _T(',') << operationalPeriod;
    co << vCrlf;
    co << _T(',') << _T(',') << _T(',') << _T("Unit Name Designator") << vCrlf;
    co << _T(',') << _T(',') << _T(',') << _T("Unit Leader: Name") << _T(',') << name << vCrlf;
    co << _T(',') << _T(',') << _T(',') << _T("Position") << _T(',') << leaderPosition << vCrlf;
    }

  else {
    co << _T("ICS 214a Unit Log") << _T(',') << _T("Incident Name") << _T(',') << _T("Date Prepared");
    co << _T(',') << _T("Time Prepared") << vCrlf;
    co << _T(',') << name;
    co << _T(',') << prepDate;
    co << _T(',') << prepTime << vCrlf;

    co << _T("Unit Name Designator") << _T(',') << _T("Unit Leader: Name") << _T(',');
    co << _T("Position") << _T(',') << _T("Operational Period") << vCrlf;
    co << _T(',') << leaderName;
    co << _T(',') << leaderPosition;
    co << _T(',') << operationalPeriod << vCrlf << vCrlf;
    }

  co << _T("Date") << _T(',') << _T("Start Time") << _T(',') << _T("End Date") << _T(',');
  co << _T("End Time") << _T(',') << _T("Activity") << vCrlf;

  storeLogData(ar);

  CTimeSpan total = getTotalTime();
  LONGLONG  secs  = total.GetTotalSeconds();
  double    ttl;
  String    t;

  ttl = (double) secs / 3600.0;   t.format(_T("%0.2f"), ttl);

/*
Footer
,,,,
,Total Time:,,501.2,hours
,,,Prepared By,Bob
ICS 214a,,,Mission Number,102
,,,,
,,,,
*/

  co << vCrlf;
  co << _T(',') << _T("Total Time:") << _T(',') << _T(',') << t << _T(',') << _T("hours") << vCrlf;

  co << vCrlf << vCrlf;

  if (options.excelOne) {
    co << _T(',') << _T(',') << _T(',') << _T("Prepared By") << _T(',') << preparedBy  << vCrlf;
    co << _T("ICS 214a") << _T(',') << _T(',') << _T(',') << _T("Mission Number");
    co << _T(',') << missionNo << vCrlf;
    }
  else {
    co << _T("ICS 214a") << _T(',') << _T("Prepared By") << _T(',');
    co << _T(',') << _T("Mission Number") << vCrlf;
    co << _T(',') << preparedBy << _T(',') << _T(',') << missionNo << vCrlf;
    }
  }


void Activity::storeHeader(Archive& ar) {
CSVout co(ar);

  co << name              << _T(',');
  co << prepDate          << _T(',');
  co << prepTime          << _T(',');
  co << leaderName        << _T(',');
  co << leaderPosition    << _T(',');
  co << operationalPeriod << _T(',');
  co << preparedBy        << _T(',');
  co << missionNo         << vCrlf;
  }


void Activity::storeLogData(Archive& ar) {
int n = log.end();
int i;

  for (i = 0; i < n; i++) {log[i].store(ar);}
  }


void Activity::storeIncrLogData(Archive& ar) {
int n = log.end();
int i;

  for (i = 0; i < n; i++) {LogData& data = log[i];   if (!data.archived) {data.store(ar);}}
  }


CTimeSpan Activity::getTotalTime() {
int       n = log.end();
int       i;
CTimeSpan total = 0;

  for (i = 0; i < n; i++) {total += log[i].deltaT;}

  return total;
  }


int LogData::wrap(Display& dev, CDC* dc) {
bool dateOutIsPresent;
int  tab = dateOutTab(dateOutIsPresent);

  dev << dCR << dClrTabs << dSetTab(tab) << dTab;

  wrp.initialize(dc, dev.remaining(), false);     dev<< dCR << dClrTabs;

  return wrp(desc);
  }


CTimeSpan LogData::display(int& noLines) {
bool dateOutIsPresent;
int  tab = dateOutTab(dateOutIsPresent);

  notePad << nClrTabs << nSetTab(7) << nSetRTab(tab-1) << nSetTab(tab);

  notePad << date << nTab << timeIn << nTab;

  if (dateOutIsPresent) notePad << dateOut << _T(" ");

  notePad << timeOut << nTab;

  noLines += displayDesc();

  notePad << nCrlf;

  return deltaT;
  }


int LogData::dateOutTab(bool& dateOutIsPresent)
                            {dateOutIsPresent = !dateOut.isEmpty();   return dateOutIsPresent ? 24 : 18;}


int LogData::displayDesc() {
int i;
int n = wrp.lines.end();

  for (i = 0; i < n; i++) {

    if (i) notePad << nCrlf << nTab << nTab << nTab;

    notePad << wrp.lines[i];
    }

  return n;
  }



void LogData::set(TCchar* dt, TCchar* tmIn, TCchar* dtOut, TCchar* tmOut, TCchar* dsc) {

  date    = normalizeDate(dt);
  timeIn  = normalizeTime(tmIn);
  setStop(dtOut, tmOut);
  desc    = dsc;   desc.trim();

  setDeltaT();
  }


void LogData::setDeltaT() {
String dateO;
String s;
Date   dIn;
Date   dOut;

  dateO = dateOut.isEmpty() ? date : dateOut;

  if (date.isEmpty() || timeIn.isEmpty() || dateO.isEmpty() || timeOut.isEmpty()) {deltaT = 0; return;}

  s = date  + _T(' ') + timeIn;  dIn  = s;
  s = dateO + _T(' ') + timeOut; dOut = s;

  deltaT = dOut - dIn;
  }



void LogData::setStop(TCchar* dtOut, TCchar* tmOut) {
  dateOut = normalizeDate(dtOut);
  timeOut = normalizeTime(tmOut);

  if (dateOut == date) dateOut.clear();

  setDeltaT();
  }


void LogData::get(String& dt, String& tmIn, String& dtOut, String& tmOut, String& dsc)
                              {dt = date; tmIn = timeIn; dtOut = dateOut;  tmOut = timeOut; dsc = desc;}



void LogData::store(Archive& ar) {
CSVout co(ar);

  co << date    << _T(',');
  co << timeIn  << _T(',');
  if (dateOut.isEmpty()) co << date; else co << dateOut;   co << _T(',');
  co << timeOut << _T(',');
  co << desc    << vCrlf;
  archived = true;
  }



CTimeSpan operator+  (CTimeSpan& t, LogData& ld) {
LONGLONG sec = t.GetTotalSeconds();
LONGLONG sc1 = ld.deltaT.GetTotalSeconds();
CTimeSpan sp(sec + sc1); return sp;
  }


CTimeSpan operator+= (CTimeSpan t, LogData& ld) {return t += ld.deltaT;}




#if 0
void Activity::display() {
int       n = log.end();
int       i;
CTimeSpan totalTime = 0;
LONGLONG  secs;
String    t;
int       noLines = 0;

  notePad.clear();

  notePad << nClrTabs << nSetTab(18) << nSetTab(38) << nSetTab(55);

  notePad << nBold << nFSize(160) << _T("ICS 214a Unit Log") << nFont << nFont;
  notePad << nTab << nFSize(90) << _T("Incident Name") << nTab << _T("Date Prepared");
  notePad << nTab << _T("Time Prepared") << nFont;
  notePad << nCrlf;
  notePad << nBold << _T("SJ RACES") << nFont;
  notePad << nTab << name;
  notePad << nTab << prepDate;
  notePad << nTab << prepTime;
  notePad << nCrlf << nCrlf;
  notePad << nFSize(90) << _T("Unit Name Designator") << nTab << _T("Unit Leader: Name");
  notePad << nTab << _T("Position") << nTab << _T("Operational Period") << nFont << nCrlf;
  notePad << _T("San Jose RACES");
  notePad << nTab << leaderName;
  notePad << nTab << leaderPosition << nTab;
  dsplyWrap(operationalPeriod, 24, 3);
  notePad << nCrlf << nCrlf;

  notePad << nClrTabs << nSetTab(6) << nSetRTab(17) << nSetTab(18);
  notePad << nFSize(90) << _T("Date") << nTab << _T("Start Time") << nTab << _T("End Time");
  notePad << nTab << _T("Activity") << nFont << nCrlf;

  notePad << nClrTabs << nSetTab(7) << nSetRTab(17) << nSetTab(18) << nSetTab(24);

  for (i = 0; i < n; i++) totalTime += log[i].display(noLines);

  secs  = totalTime.GetTotalSeconds();
  double ttl = (double) secs / 3600.0;
  t.format(_T("%0.2f"), ttl);

  notePad << nCrlf << _T("   Total Time:") << nTab << t << nTab << _T("hours") << nCrlf;
  }
#endif

