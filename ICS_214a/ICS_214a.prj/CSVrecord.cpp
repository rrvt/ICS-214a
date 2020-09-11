// CSV Record


#include "stdafx.h"
#include "CSVrecord.h"


void CSVrecord::clear() {
  date.clear();
  timeIn.clear();
  dateOut.clear();
  timeOut.clear();
  desc.clear();
  data6.clear();
  data7.clear();
  data8.clear();
  CSVRcdB::clear();
  }



void CSVrecord::put(TCchar* s) {
  switch ((putI)) {
    case 0: date    = s; break;
    case 1: timeIn  = s; break;
    case 2: dateOut = s; break;
    case 3: timeOut = s; break;
    case 4: desc    = s; break;
    case 5: data6   = s; break;
    case 6: data7   = s; break;
    case 7: data8   = s; break;
    }
  }


String* CSVrecord::CSVrecord::get() {
  switch (getI) {
    case 0: return &date;
    case 1: return &timeIn;
    case 2: return &dateOut;
    case 3: return &timeOut;
    case 4: return &desc;
    case 5: return &data6;
    case 6: return &data7;
    case 7: return &data8;
    }
  return 0;
  }


void CSVrecord::copy(CSVrecord& r) {
  date    = r.date;
  timeIn  = r.timeIn;
  dateOut = r.dateOut;
  timeOut = r.timeOut;
  desc    = r.desc;
  data6   = r.data6;
  data7   = r.data7;
  data8   = r.data8;
  CSVRcdB::copy(r);
  }

