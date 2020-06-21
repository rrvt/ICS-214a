// ICS-214a -- Activity Log


#pragma once
#include "Archive.h"
#include "CSVrecord.h"
#include "Date.h"
#include "Expandable.h"


class LogData {
String date;
String timeIn;
String dateOut;
String timeOut;
String desc;


public:

CTimeSpan deltaT;
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

  CTimeSpan display();

private:

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

enum StoreType {NilStore, StoreAll, StoreIncr};

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

  Activity() : storeType(NilStore) { }
 ~Activity() { }

  void     clear();

  void     load(Archive&  ar);
  void     setStoreAll()  {storeType = StoreAll;}
  void     setStoreIncr() {storeType = StoreIncr;}
  void     store(Archive& ar);

  void     add(TCchar* date, TCchar* timeIn, TCchar* timeOut, TCchar* desc);
  LogData* entry(int i) {return i < log.end() ? &log[i] : 0;}

  void     display();

private:

  bool loadHeader(CSVrecord& rcd);
  void loadLog(   CSVrecord& rcd);
  bool storeHeader(Archive& ar);
  bool storeLogData(Archive& ar);

  friend class ActivityIter;
  };


class ActivityIter {
int       logX;
Activity& activity;

public:

  ActivityIter(Activity& actLog) : activity(actLog), logX(0) { }

  LogData* operator() ()    {logX = 0; return logX < activity.log.end() ? &activity.log[logX] : 0;}
  LogData* operator++ (int) {logX++;   return logX < activity.log.end() ? &activity.log[logX] : 0;}

private:

  ActivityIter() : activity(*(Activity*) 0), logX(0) { }
  };


extern Activity activity;
