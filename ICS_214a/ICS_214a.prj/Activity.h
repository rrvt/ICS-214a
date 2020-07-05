// ICS-214a -- Activity Log


#pragma once
#include "Archive.h"
#include "CSVrecord.h"
#include "Date.h"
#include "Display.h"
#include "Expandable.h"
#include "Wrap.h"


class LogData {
String date;
String timeIn;
String dateOut;
String timeOut;
String desc;

public:

CTimeSpan deltaT;
Wrap      wrp;
bool      archived;

  LogData() : archived(false), deltaT(0) { }
  LogData(LogData& ld) {copy(ld);}
 ~LogData() { }

  LogData&  operator= (LogData& ld) {copy(ld); return *this;}

  void      set(TCchar* dt, TCchar* tmIn, TCchar* dtOut, TCchar* tmOut, TCchar* dsc);
  void      setStop(TCchar* dtOut, TCchar* tmOut);
  void      get(String& dt, String& tmIn, String& dtOut, String& tmOut, String& dsc);
  void      setDeltaT();

  void      store(Archive& ar);
  void      load(CSVrecord& rcd);

  int       wrap(Display& dev, CDC* dc);
  int       noLines() {return wrp.lines.end();}
  CTimeSpan display(int& noLines);

private:

  int  displayDesc();
  int  dateOutTab(bool& dateOutIsPresent);

  void copy(LogData& ld) {
    date = ld.date; timeIn = ld.timeIn; dateOut = ld.dateOut; timeOut = ld.timeOut;
    desc = ld.desc; archived = ld.archived;  deltaT = ld.deltaT;
    }
  friend CTimeSpan operator+  (CTimeSpan t, LogData& ld);
  friend CTimeSpan operator+= (CTimeSpan t, LogData& ld);
  };


CTimeSpan operator+  (CTimeSpan& t, LogData& ld);
CTimeSpan operator+= (CTimeSpan& t, LogData& ld);


class Activity {

enum StoreType {NilStore, StoreIncr, StoreAll, StoreExcel};

StoreType storeType;

Expandable<LogData, 2> log;

public:

String name;
String prepDate;
String prepTime;
String leaderName;
String leaderPosition;
String operationalPeriod;             // Dates any way they want to display them
String preparedBy;
String missionNo;

Wrap   opPeriod;                      // Used during reporting only


  Activity() : storeType(NilStore) { }
 ~Activity() { }

  void     clear();

  int       wrapOpPer(int tab, Display& dev, CDC* dc);
  int       dspOpPer();

  void     load(Archive&  ar);
  void     setStoreAll()   {storeType = StoreAll;}
  void     setStoreIncr()  {storeType = StoreIncr;}
  void     setStoreExcel() {storeType = StoreExcel;}
  void     store(Archive& ar);

  void     add(TCchar* date, TCchar* timeIn, TCchar* timeOut, TCchar* desc);
  LogData* entry(int i) {return i < log.end() ? &log[i] : 0;}

private:

  void      storeIncr( Archive&  ar);
  void      storeAll(  Archive&  ar);
  void      storeExcel(Archive&  ar);
  bool      loadHeader(CSVrecord& rcd);
  void      loadLog(   CSVrecord& rcd);
  void      storeHeader(Archive& ar);
  void      storeLogData(Archive& ar);
  void      storeIncrLogData(Archive& ar);
  CTimeSpan getTotalTime();

  friend class ActivityIter;
  friend class Report;
  };


class ActivityIter {
int       logX;
Activity& activity;

public:

  ActivityIter(Activity& actLog) : activity(actLog), logX(0) { }

  LogData* operator() ()    {logX = 0; return logX < activity.log.end() ? &activity.log[logX] : 0;}
  LogData* operator++ (int) {logX++;   return logX < activity.log.end() ? &activity.log[logX] : 0;}
  bool     last()           {return logX + 1 == activity.log.end();}

private:

  ActivityIter() : activity(*(Activity*) 0), logX(0) { }
  };


extern Activity activity;
