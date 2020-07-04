// Wrap --


#pragma once
#include "Expandable.h"


class Wrap {
CDC* dc;
int  extent;
bool isItalic;

public:

Expandable<String, 2> lines;

  Wrap() { }
 ~Wrap() { }

  void initialize(CDC* pDC, int widthLeft, bool isItalic);

  int operator() (TCchar* p);        //, int noChars, int noTabs

private:

  int  findLast(Tchar ch, String& s);
  int  findLastChar(String& s);
  int  width(String& s);

  int  findLastWh(String& s, int noChars);
  };

