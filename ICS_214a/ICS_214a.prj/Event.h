// A Single Event


#pragma once
#include "Date.h"
//#include "Wrap.h"

class Archive;
class CSVrecord;
class DevStream;
class NotePad;


class Event {
public:

Date      startTime;
Date      endTime;
String    desc;

CTimeSpan deltaT;
#ifdef WrapDbg
Wrap      wrap;
#endif
bool      archived;

  Event() : /*wrap(true),*/ archived(false), deltaT(0) { }
  Event(Event& event) /*: wrap(true)*/ {copy(event);}
 ~Event() { }

  Event&    operator= (Event& event) {copy(event); return *this;}

  void      set(TCchar* dt, TCchar* tmIn, TCchar* dtOut, TCchar* tmOut, TCchar* dsc);
  void      setStop(TCchar* dtOut, TCchar* tmOut);
  void      setDeltaT();

  void      store(Archive& ar);
  void      load(CSVrecord& rcd);

//  void      clearWrap() {wrap.clear();}
//  int       wrapIt(DevStream& dev, CDC* dc);
//  int       noLines() {return wrap.noLines();}     int& noLines,
  CTimeSpan display(NotePad& np);

private:

  int  dateOutTab(bool& dateOutIsPresent);

  void copy(Event& event);

  friend CTimeSpan operator+  (CTimeSpan t, Event& event);
  friend CTimeSpan operator+= (CTimeSpan t, Event& event);
  };


CTimeSpan operator+  (CTimeSpan& t, Event& event);
CTimeSpan operator+= (CTimeSpan& t, Event& event);

