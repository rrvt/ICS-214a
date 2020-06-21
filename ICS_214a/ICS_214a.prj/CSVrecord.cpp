// CSV Record


#include "stdafx.h"
#include "CSVrecord.h"
#include "Csv.h"


bool CSVrecord::load() {
String nullStg = _T("");
Token* tok;
Token* tok1;

  startStore();

  while (csv.get_token() != EOFToken) {
    tok = csv.token;   tok1 = csv.token1;

    if (tok->code  == EolToken)   {                       csv.accept_token();      return true;}

    if (tok->code  == CommaToken) {saveStore();           csv.accept_token();      continue;}

    if (tok1->code == CommaToken) {saveStore(tok->name);  csv.accept_two_tokens(); continue;}

    if (tok1->code == EolToken)   {saveStore(tok->name);  csv.accept_token();      continue;}

    if (tok1->code == EOFToken)   {saveStore(tok->name);  csv.accept_token();      continue;}
    }

  return false;
  }





static TCchar quote = _T('"');


String& CSVout::quotes(TCchar* p) {
static String s;
bool          addQuotes = false;

  s = p;

  if (s.find(quote) >= 0) {
    String t;
    int    n = s.length();
    int    i;

    for (i = 0; i < n; i++) {Tchar ch = s[i];   if (ch == quote) t += quote;   t += ch;}

    s = t; addQuotes = true;
    }

  if (s.find(_T(',')) >= 0) addQuotes = true;

  if (addQuotes) s = quote + s + quote;

  return s;
  }



CSVManip vCrlf;                  // add to stream to terminate a line on display: dsp << "xyz" << vCrlf;

void CSVout::initialize() {vCrlf.n = this; vCrlf.func = CSVout::doCrlf;}

