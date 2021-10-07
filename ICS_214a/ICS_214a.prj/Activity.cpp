// ICS-214a -- Activity Log


#include "stdafx.h"
#include "Activity.h"
#include "CSVOut.h"
#include "EditEntryDlg.h"
#include "EventLogDlg.h"
#include "Options.h"
#include "StopEntryDlg.h"
#include "Utilities.h"


Activity activity;


void Activity::clear() {
  storeType = NilStore;
  log.clear();

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
LogData& data = log.nextData();

  data.set(date, timeIn, 0, timeOut, desc);
  }


void Activity::load(Archive& ar) {
CSVLex    lex(ar);
CSVrecord rcd;

  if (!loadHeader(lex)) return;

  log.clear();

  while (rcd.load(lex)) log.nextData().load(rcd);
  }


bool Activity::loadHeader(CSVLex& lex) {
CSVrecord rcd;

  if (!rcd.load(lex)) return false;

  name              = rcd.date;
  prepDate          = rcd.timeIn;
  prepTime          = rcd.dateOut;
  leaderName        = rcd.timeOut;
  leaderPosition    = rcd.desc;
  operationalPeriod = rcd.data6;
  preparedBy        = rcd.data7;
  missionNo         = rcd.data8;

  return true;
  }


void LogData::load(CSVrecord& rcd) {
String s;

  s = rcd.date    + _T(' ') + rcd.timeIn;    startTime = s;
  s = rcd.dateOut + _T(' ') + rcd.timeOut;   endTime   = s;
  desc = rcd.desc;

  setDeltaT();  archived = true;
  }

bool Activity::logEntry() {
EventLogDlg dlg;

  dlg.logDate   = getDateNow();
  dlg.startTime = getTimeNow();

  if (dlg.DoModal() != IDOK) return false;

  add(dlg.logDate, dlg.startTime, dlg.endTime, dlg.logActivity); return true;  //setStoreIncr();
  }


bool Activity::stopEntry() {
StopEntryDlg dlg;

  dlg.stopDate = getDateNow();
  dlg.stopTime = getTimeNow();

  if (dlg.DoModal() != IDOK) return false;

     return true;
  }                                              //setStoreAll();  activity.setStoreAll();


bool Activity::editLogEntry() {
EditEntryDlg dlg;

  if (dlg.DoModal() != IDOK) return false;

   return true;
  }



void Activity::storeIncr(Archive&  ar) {
int n = log.end();
int i;

  for (i = 0; i < n; i++) {LogData& data = log[i];   if (!data.archived) {data.store(ar);}}
  }


void Activity::storeAll(Archive&  ar) {
CSVOut co(ar);

  co << name              << _T(',');
  co << prepDate          << _T(',');
  co << prepTime          << _T(',');
  co << leaderName        << _T(',');
  co << leaderPosition    << _T(',');
  co << operationalPeriod << _T(',');
  co << preparedBy        << _T(',');
  co << missionNo         << vCrlf;

  storeLogData(ar);
  }


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
CSVOut co(ar);

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


void Activity::storeLogData(Archive& ar) {
int n = log.end();
int i;

  for (i = 0; i < n; i++) {log[i].store(ar);}
  }


CTimeSpan Activity::getTotalTime() {
int       n = log.end();
int       i;
CTimeSpan total = 0;

  for (i = 0; i < n; i++) {total += log[i].deltaT;}

  return total;
  }


int LogData::wrap(Device& dev, CDC* dc) {
bool dateOutIsPresent;
int  tab     = dateOutTab(dateOutIsPresent);
int  chWidth = dev.flChWidth();

  dev << dCR << dClrTabs << dSetTab(tab) << dTab;

  wrp.initialize(dc, dev.remaining(), dev.maxWidth(), false);     dev<< dCR << dClrTabs;   // - 3 * chWidth

  return wrp(desc);
  }



CTimeSpan LogData::display(int& noLines, NotePad& np) {
bool   dateOutIsPresent;
int    tab = dateOutTab(dateOutIsPresent);
String s;

  np << nClrTabs << nSetTab(7) << nSetRTab(tab-1) << nSetTab(tab);

  np << startTime.getDate() << nTab << startTime.getHHMM() << nTab;

  if (endTime > startTime) {
    if (dateOutIsPresent) np << endTime.getDate() << _T(" ");

    np << endTime.getHHMM() << nTab;
    }
  else np << _T(" ") << nTab;

  np << wrp << nCrlf;   noLines += wrp.noLines();

  return deltaT;
  }


int LogData::dateOutTab(bool& dateOutIsPresent) {
String dtin  = startTime.getDate();
String dtout = endTime.getDate();

  dateOutIsPresent = dtout != dtin;   return dateOutIsPresent ? 24 : 18;
  }


void LogData::set(TCchar* dt, TCchar* tmIn, TCchar* dtOut, TCchar* tmOut, TCchar* dsc) {

String date    = normalizeDate(dt);
String timeIn  = normalizeTime(tmIn);
Date   d;        d.getToday();
String s;

  if (date.isEmpty())   date   = d.getDate();
  if (timeIn.isEmpty()) timeIn = d.getHHMM();
  s = date + _T(' ') + timeIn;   startTime = s;

  setStop(dtOut, tmOut);   desc = dsc;   desc.trim();
  }



void LogData::setStop(TCchar* dtOut, TCchar* tmOut) {
String dateOut = normalizeDate(dtOut);
String timeOut = normalizeTime(tmOut);
bool   noDate  = dateOut.isEmpty();
bool   noTime  = timeOut.isEmpty();
String s;

  if (noDate && noTime) endTime = startTime;

  else {
    if (dateOut.isEmpty()) dateOut == startTime.getDate();
    if (timeOut.isEmpty()) timeOut == startTime.getHHMM();
    s = dateOut + _T(' ') + timeOut;   endTime = s;
    }

  setDeltaT();
  }


void LogData::setDeltaT() {deltaT = endTime > startTime ? endTime - startTime : 0;}




void LogData::store(Archive& ar) {
CSVOut co(ar);

  co << startTime.getDate() << _T(',');
  co << startTime.getHHMM() << _T(',');
  co << endTime.getDate()   << _T(',');
  co << endTime.getHHMM()   << _T(',');
  co << desc    << vCrlf;
  archived = true;
  }



void LogData::copy(LogData& ld) {
  startTime = ld.startTime;  endTime = ld.endTime;
  desc = ld.desc;  deltaT = ld.deltaT;  wrp = ld.wrp;   archived = ld.archived;
  }



CTimeSpan operator+  (CTimeSpan& t, LogData& ld) {
LONGLONG sec = t.GetTotalSeconds();
LONGLONG sc1 = ld.deltaT.GetTotalSeconds();
CTimeSpan sp(sec + sc1); return sp;
  }


CTimeSpan operator+= (CTimeSpan t, LogData& ld) {return t += ld.deltaT;}



#if 0
void Activity::store(Archive& ar) {
  switch (storeType) {
    case StoreIncr  : storeIncr(ar);  break;
    case StoreAll   : storeAll(ar);   break;
    case StoreExcel : storeExcel(ar); break;
    }
  }
#endif
#if 0
void Activity::storeIncrLogData(Archive& ar) {
int n = log.end();
int i;

  for (i = 0; i < n; i++) {LogData& data = log[i];   if (!data.archived) {data.store(ar);}}
  }
#endif
#if 0
void Activity::storeHeader(Archive& ar) {
CSVOut co(ar);

  co << name              << _T(',');
  co << prepDate          << _T(',');
  co << prepTime          << _T(',');
  co << leaderName        << _T(',');
  co << leaderPosition    << _T(',');
  co << operationalPeriod << _T(',');
  co << preparedBy        << _T(',');
  co << missionNo         << vCrlf;
  }
#endif
#if 0
void LogData::get(String& dt, String& tmIn, String& dtOut, String& tmOut, String& dsc) {

  dt = startTime.getDate(); tmIn = startTime.getHHMM();

  dtOut = endTime.getDate();  tmOut = endTime.getHHMM(); dsc = desc;
  }
#endif

