// ICS-214a -- Activity Log


#pragma once
#include "Event.h"
#include "Expandable.h"
#include "IterT.h"

class CSVLex;


// Define an iterator

class Activity;
typedef IterT<Activity, Event> ActyIter;                // Establish the typename so it can be friended


class Activity {

enum StoreType {NilStore, StoreIncr, StoreAll, StoreExcel};

StoreType storeType;

Expandable<Event, 2> data;

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
  void     storeExcel(Archive&  ar, bool option1 = false);

  bool     logEntry();
  bool     stopEntry();
  bool     editLogEntry();

  void     add(TCchar* date, TCchar* timeIn, TCchar* timeOut, TCchar* desc);
  Event*   entry(int i) {return i < data.end() ? &data[i] : 0;}

private:

  bool      loadHeader(CSVLex& lex);
  void      storeLogData(Archive& ar);
  CTimeSpan getTotalTime();

private:

  // returns either a pointer to data (or datum) at index i in array or zero
  Event* datum(int i) {return 0 <= i && i < data.end() ? &data[i] : 0;}

  int nData() {return data.end();}      // returns number of data items in array

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
  //  void      storeHeader(Archive& ar);
//  void      storeIncrLogData(Archive& ar);
//  friend class ActivityIter;

