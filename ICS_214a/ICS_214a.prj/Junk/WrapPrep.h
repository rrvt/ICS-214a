// WrapPrep and Display a String


#pragma once
#include "Expandable.h"


class WrapPrep {
int nTabs;

public:

Expandable<String, 2> lines;

  WrapPrep() { }
 ~WrapPrep() { }

  int operator() (TCchar* p, int noChars, int noTabs);

  int noLines() {return lines.end();}

  int display();

private:

  int findLastWh(String& s, int noChars);
  };

