// ICS-214a -- Activity Log


#include "stdafx.h"
#include "Activity.h"
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
      case 2: dateOut = fld->name; break;
      case 3: timeOut = fld->name; break;
      case 4: desc    = fld->name; break;
      }
    }

  setDeltaT();  archived = true;
  }


void Activity::store(Archive& ar) {
  if (storeType == StoreAll && !storeHeader(ar)) return;

  storeLogData(ar);   return;
  }


bool Activity::storeHeader(Archive& ar) {
CSVout co(ar);

  co << name              << _T(',');
  co << prepDate          << _T(',');
  co << prepTime          << _T(',');
  co << leaderName        << _T(',');
  co << leaderPosition    << _T(',');
  co << operationalPeriod << _T(',');
  co << preparedBy        << _T(',');
  co << missionNo         << vCrlf;
  return true;
  }


bool Activity::storeLogData(Archive& ar) {
int n = log.end();
int i;

  for (i = 0; i < n; i++) {
    LogData& data = log[i];

    if (storeType == StoreAll) {data.store(ar);}
    else if (!data.archived)   {data.store(ar);}
    }

  return true;
  }


void Activity::display() {
int       n = log.end();
int       i;
CTimeSpan totalTime = 0;
LONGLONG  secs;
String    t;

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

  for (i = 0; i < n; i++) totalTime += log[i].display();

  secs  = totalTime.GetTotalSeconds();
  double ttl = (double) secs / 3600.0;
  t.format(_T("%0.2f"), ttl);

  notePad << nCrlf << _T("   Total Time:") << nTab << t << nTab << _T("hours") << nCrlf;
  }


CTimeSpan LogData::display() {
bool dateOutPresent = !dateOut.isEmpty();
int  descLng  = 90 - (dateOutPresent ? 24 : 18);
int  descTabs = dateOutPresent ? 4 : 3;

  notePad << date << nTab << timeIn;

  if (dateOutPresent) notePad << nTab << dateOut;

  notePad << nTab << timeOut << nTab;

  dsplyWrap(desc, descLng, descTabs);

  notePad << nCrlf;

  return deltaT;
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
  co << dateOut << _T(',');
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

