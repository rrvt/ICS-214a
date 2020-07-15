// Wrap --


#pragma once
#include "Expandable.h"


class Wrap {
bool enabled;
CDC* dc;
int  extent;
bool isItalic;

int                   i;
Expandable<String, 2> lines;

public:

  Wrap()            : enabled(true), dc(0), extent(0), isItalic(false) { }
  Wrap(bool enable) : enabled(enable) { }
  Wrap(Wrap& w) {copy(w);}
 ~Wrap() { }

  Wrap& operator= (Wrap& w) {copy(w); return *this;}

  void initialize(CDC* pDC, int widthLeft, bool isItalic);

  int operator() (TCchar* p);        //, int noChars, int noTabs

  bool isEmpty() {return lines.end() == 0;}
  int  noLines() {return lines.end();}

  String* startLoop() {i = 0; return i < lines.end() ? &lines[i] : 0;}
  String* nextLine()  {i++;   return i < lines.end() ? &lines[i] : 0;}

private:

  void copy(Wrap& w)
          {enabled = w.enabled; dc = w.dc; extent = w.extent; isItalic =   w.isItalic; lines = w.lines;}

  int  findLast(Tchar ch, String& s);
  int  findLastChar(String& s);
  int  width(String& s);

  int  findLastWh(String& s, int noChars);

  };

