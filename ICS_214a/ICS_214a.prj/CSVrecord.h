// CSV Record


#pragma once
#include "Archive.h"
#include "Csv.h"
#include "Expandable.h"


class CSVfield {
public:
String name;

  CSVfield() {}
  CSVfield(CSVfield& fd) {copy(fd);}

 ~CSVfield() {}

  void      clear()                {name.clear();}
  bool      isEmpty()              {return name.isEmpty();}

  CSVfield& operator<< (String& s) {name += s; return *this;}

  CSVfield& operator=(CSVfield& fd) {copy(fd); return *this;}

private:

  void copy(CSVfield& src) {name = src.name;}
  };


class CSVrecord {
Csv                        csv;

int                        i;
Expandable <CSVfield, 128> fields;

public:

  CSVrecord(Archive& ar) : csv(ar), i(0) {}
 ~CSVrecord() { }

  bool      load();

  void      freeFields();

  int       nFields() {return fields.end();}

  int       notEmptyNo() {int i = fields.end(); return fields[i-1].isEmpty() ? 0 : i;}

  void      dspFields() {dspFields(fields.end());}

  void      dspFields(int n);

  CSVfield* startLoop() {i = 0; return i < nFields() ? &fields[i] : 0;}
  CSVfield* nextFld()   {i++;   return i < nFields() ? &fields[i] : 0;}

private:

  void startStore() {fields.clr();}
  void saveStore(TCchar* name = 0) {fields[fields.end()].name = name ? name : _T("");}
       CSVrecord() : csv(*(Archive*)0) {}
  };


class CSVout;

typedef ManipT<CSVout> CSVManip;

class CSVout {
Archive& ar;

public:

  CSVout(Archive& a) : ar(a) {initialize();}

  CSVout& operator<< (String&    s)     {ar.write(quotes(s));  return *this;}
  CSVout& operator<< (TCchar*    p)     {ar.write(quotes(p));  return *this;}
  CSVout& operator<< (Tchar     ch)     {ar.write(ch); return *this;}
  CSVout& operator<< (int        x)     {ar.write(x);  return *this;}
  CSVout& operator<< (CSVManip& m)      {return m.func(*this);}

  void    crlf()                        {ar.crlf();}

private:

  static String& quotes(TCchar* p);

  void initialize();

  static CSVout& doCrlf(CSVout& n) {n.crlf(); return n;}

  CSVout() : ar(*( Archive*) 0) { }
  };


extern CSVManip vCrlf;       // add to stream to terminate a line on display: ar << "xyz" << vCrlf;

