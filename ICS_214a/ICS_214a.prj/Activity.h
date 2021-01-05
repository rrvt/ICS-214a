// ICS-214a -- Activity Log


#pragma once
#include "Archive.h"
#include "CSVrecord.h"
#include "Date.h"
#include "Device.h"
#include "Expandable.h"
#include "IterT.h"
#include "Wrap.h"


class LogData {
public:

Date      startTime;
Date      endTime;
String    desc;

CTimeSpan deltaT;
Wrap      wrp;
bool      archived;

  LogData() : wrp(true), archived(false), deltaT(0) { }
  LogData(LogData& ld) : wrp(true) {copy(ld);}
 ~LogData() { }

  LogData&  operator= (LogData& ld) {copy(ld); return *this;}

  void      set(TCchar* dt, TCchar* tmIn, TCchar* dtOut, TCchar* tmOut, TCchar* dsc);
  void      setStop(TCchar* dtOut, TCchar* tmOut);
  void      setDeltaT();

  void      store(Archive& ar);
  void      load(CSVrecord& rcd);

  int       wrap(Device& dev, CDC* dc);
  int       noLines() {return wrp.noLines();}
  CTimeSpan display(int& noLines, NotePad& np);

private:

  int  dateOutTab(bool& dateOutIsPresent);

  void copy(LogData& ld);

  friend CTimeSpan operator+  (CTimeSpan t, LogData& ld);
  friend CTimeSpan operator+= (CTimeSpan t, LogData& ld);
  };


CTimeSpan operator+  (CTimeSpan& t, LogData& ld);
CTimeSpan operator+= (CTimeSpan& t, LogData& ld);


// Define an iterator

class Activity;
typedef IterT<Activity, LogData> ActyIter;                // Establish the typename so it can be friended


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

  Activity() : storeType(NilStore) { }
 ~Activity() { }

  void     clear();

  void     load(Archive& ar);

  void     storeAll(  Archive&  ar);
  void     storeIncr( Archive&  ar);
  void     storeExcel(Archive&  ar);

  bool     logEntry();
  bool     stopEntry();
  bool     editLogEntry();

  void     add(TCchar* date, TCchar* timeIn, TCchar* timeOut, TCchar* desc);
  LogData* entry(int i) {return i < log.end() ? &log[i] : 0;}

private:

  bool      loadHeader(CSVLex& lex);
//  void      storeHeader(Archive& ar);
  void      storeLogData(Archive& ar);
//  void      storeIncrLogData(Archive& ar);
  CTimeSpan getTotalTime();

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  LogData* datum(int i) {return 0 <= i && i < log.end() ? &log[i] : 0;}

  // returns number of data items in array
  int nData() {return log.end();}

//  friend class ActivityIter;
  friend class Report;
  friend typename ActyIter;
  };


extern Activity activity;




#if 0
  void     setStoreAll()   {storeType = StoreAll;}
  void     setStoreIncr()  {storeType = StoreIncr;}
  void     setStoreExcel() {storeType = StoreExcel;}
//  void     store(Archive& ar);
#endif

