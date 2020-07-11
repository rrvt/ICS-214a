// Global Options


#pragma once


struct Options {
bool   excelOne;
String topMargin;
String leftMargin;
String rightMargin;
String botMargin;

  Options() : excelOne(false), topMargin(0.0), leftMargin(0.0), rightMargin(0.0), botMargin(0.0) { }
 ~Options() { }

  void load();
  void store();
  };

extern Options options;

