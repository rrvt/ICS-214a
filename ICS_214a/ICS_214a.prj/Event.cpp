// A Single Event


#include "stdafx.h"
#include "Event.h"
#include "CSVOut.h"
#include "CSVrecord.h"
#include "DevStream.h"
#include "Utilities.h"


void Event::load(CSVrecord& rcd) {
String s;

  s = rcd.date    + _T(' ') + rcd.timeIn;    startTime = s;
  s = rcd.dateOut + _T(' ') + rcd.timeOut;   endTime   = s;
  desc = rcd.desc;

  setDeltaT();  archived = true;
  }


CTimeSpan Event::display(NotePad& np) {
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

  np << desc << nCrlf;

  return deltaT;
  }


int Event::dateOutTab(bool& dateOutIsPresent) {
String dtin  = startTime.getDate();
String dtout = endTime.getDate();

  dateOutIsPresent = dtout != dtin;   return dateOutIsPresent ? 24 : 18;
  }


void Event::set(TCchar* dt, TCchar* tmIn, TCchar* dtOut, TCchar* tmOut, TCchar* dsc) {
String date    = normalizeDate(dt);
String timeIn  = normalizeTime(tmIn);
Date   d;        d.getToday();
String s;

  if (date.isEmpty())   date   = d.getDate();
  if (timeIn.isEmpty()) timeIn = d.getHHMM();
  s = date + _T(' ') + timeIn;   startTime = s;

  setStop(dtOut, tmOut);   desc = dsc;   desc.trim();
  }


void Event::setStop(TCchar* dtOut, TCchar* tmOut) {
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


void Event::setDeltaT() {deltaT = endTime > startTime ? endTime - startTime : 0;}


void Event::store(Archive& ar) {
CSVOut co(ar);

  co << startTime.getDate() << _T(',');
  co << startTime.getHHMM() << _T(',');
  co << endTime.getDate()   << _T(',');
  co << endTime.getHHMM()   << _T(',');
  co << desc                << vCrlf;
  archived = true;
  }


void Event::copy(Event& event) {
  startTime = event.startTime;
  endTime   = event.endTime;
  desc      = event.desc;
  deltaT    = event.deltaT;
  archived  = event.archived;
  }


CTimeSpan operator+  (CTimeSpan& t, Event& event) {
LONGLONG  sec = t.GetTotalSeconds();
LONGLONG  sc1 = event.deltaT.GetTotalSeconds();
CTimeSpan sp(sec + sc1);    return sp;
  }


CTimeSpan operator+= (CTimeSpan t, Event& event) {return t += event.deltaT;}




#if 0
int Event::wrapIt(DevStream& dev, CDC* dc) {
bool dateOutIsPresent;
int  tab     = dateOutTab(dateOutIsPresent);
int  chWidth = dev.flChWidth();

  dev << dCR << dClrTabs << dSetTab(tab) << dTab;

  wrap.initialize(dc, dev.remaining(), dev.maxWidth(), false);     dev << dCR << dClrTabs;   // - 3 * chWidth

  return wrap(desc);
  }

int& noLines,
#endif
//  wrap      = event.wrap;
  //int    n = np.getNoLines();
//  np << wrap << nCrlf;   noLines += wrap.noLines();
//noLines += np.getNoLines() - n;

