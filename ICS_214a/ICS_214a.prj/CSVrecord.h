// CSV Record


#pragma once
#include "CSVRcdB.h"


class CSVrecord : public CSVRcdB {
public:
String date;
String timeIn;
String dateOut;
String timeOut;
String desc;
String data6;
String data7;
String data8;

  CSVrecord() { }
  CSVrecord(CSVrecord& r) {copy(r);}
 ~CSVrecord() { }

  void clear();

  CSVrecord& operator= (CSVrecord& r) {copy(r); return *this;}

private:

  virtual void    put(TCchar* s);

  virtual String* get();

  virtual void    copy(CSVrecord& r);
  };


