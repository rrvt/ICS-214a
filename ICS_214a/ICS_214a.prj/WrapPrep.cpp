// WrapPrep and Display a String


#include "stdafx.h"
#include "WrapPrep.h"
#include "NotePad.h"


int WrapPrep::operator() (TCchar* p, int noChars, int noTabs) {
String s         = p;
int    threshold = noChars * 5 / 8;
int    brkpt;
String t;
int    i;

  lines.clr();   nTabs = noTabs;

  for (i = 0; s.length() > noChars; i++) {

    brkpt = findLastWh(s, noChars);

    if (brkpt < threshold) brkpt = noChars;

    t = s.substr(0, brkpt); s = s.substr(brkpt); s.trim();

    lines[lines.end()] = t;
    }

  if (!s.isEmpty()) lines[lines.end()] = s;

  return lines.end();
  }


int WrapPrep::display() {
int i;

  for (i = 0; i < lines.end(); i++) {

    if (i) {notePad << nCrlf;   for (int j = 0; j < nTabs; j++) notePad << nTab;}

    notePad << lines[i];
    }

  return lines.end();
  }



int WrapPrep::findLastWh(String& s, int noChars) {
int   lastPos = 0;
int   n = s.length();
int   i;

  n = n < noChars ? n : noChars;

  for (i = 0; i < n; i++) if (s[i] <= _T(' ')) lastPos = i;

  return lastPos;
  }

