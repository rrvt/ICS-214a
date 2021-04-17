// Global Options


#pragma once
#include "CScrView.h"


struct Options {
bool       excelOne;
PrtrOrient orient;
String     topMargin;
String     leftMargin;
String     rightMargin;
String     botMargin;

  Options() : excelOne(false), orient(Portrait),
                                    topMargin(0.0), leftMargin(0.0), rightMargin(0.0), botMargin(0.0) { }
 ~Options() { }

  void operator() ();

  void load();
  void store();

  void setOrient(PrtrOrient v) {orient = v; store();}
  };

extern Options options;

