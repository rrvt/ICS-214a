// Utilities


#include "stdafx.h"
#include "Utilities.h"
#include "Date.h"
#include "NotePad.h"


static String blks = _T("          ");


String addTab(String& s, int max) {int n = max - s.length(); return s + blks.substr(0, n);}


String normalizeDate(TCchar* date) {
String s  = date ? date : _T("");   if (s.isEmpty()) return s;
Date   dt = s;

  s = dt.format(_T("%D"));  return s;
  }

String normalizeTime(TCchar* time) {
String s  = time ? time : _T("");   if (s.isEmpty()) return s;
Date   dt = s;

  s = dt.format(_T("%R"));  return s;
  }


String getDateNow() {Date dt;   dt.getToday();   return dt.format(_T("%D"));}

String getTimeNow() {Date dt;   dt.getToday();   return dt.format(_T("%R"));}



static int  findLastWh(String& s, int noChars);
static int wrap(int i, int noTabs);

#if 0
// Display a string of no more than noChars.  If more, the insert noTabs and no more than noChars until
// string exhausted.  Returns number of lines output

int dsplyWrap(TCchar* p, int noChars, int noTabs) {
String s = p;
int    brkpt;
int    threshold = noChars * 5 / 8;
String t;
int    i;
int    noLines = 0;

  for (i = 0; s.length() > noChars; i++) {

    noLines += wrap(i, noTabs);   brkpt = findLastWh(s, noChars);

    if (brkpt < threshold) brkpt = noChars;

    t = s.substr(0, brkpt); s = s.substr(brkpt); s.trim();

    notePad << t;
    }

  if (!s.isEmpty()) {noLines += wrap(i, noTabs); notePad << s;}

  return noLines;
  }


int findLastWh(String& s, int noChars) {
int   lastPos = 0;
int   n = s.length();
int   i;

  n = n < noChars ? n : noChars;

  for (i = 0; i < n; i++) if (s[i] <= _T(' ')) lastPos = i;

  return lastPos;
  }


int wrap(int i, int noTabs) {

  if (!i) return 0;

  notePad << nCrlf;   for (i = 0; i < noTabs; i++) notePad << nTab;  return 1;
  }
#endif
