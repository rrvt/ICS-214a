// Font Manager
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.


#pragma once
#include "Expandable.h"

/*
typedef struct tagLOGFONTW {
  LONG  lfHeight;
  LONG  lfWidth;
  LONG  lfEscapement;
  LONG  lfOrientation;
  LONG  lfWeight;
  BYTE  lfItalic;
  BYTE  lfUnderline;
  BYTE  lfStrikeOut;
  BYTE  lfCharSet;
  BYTE  lfOutPrecision;
  BYTE  lfClipPrecision;
  BYTE  lfQuality;
  BYTE  lfPitchAndFamily;
  WCHAR lfFaceName[LF_FACESIZE];
  } LOGFONTW, *PLOGFONTW, *NPLOGFONTW, *LPLOGFONTW;

*/


struct FontAttr {
CDC*   dc;
int    sz;
bool   bold;
bool   italic;
bool   underline;
bool   strikeout;
String face;

  FontAttr() : dc(0), sz(0), bold(false), italic(false), underline(false), strikeout(false) {}
  FontAttr(FontAttr& fd) {copy(fd);}

  FontAttr& operator= (FontAttr& fd) {copy(fd); return *this;}

private:

  void copy(FontAttr& src) {
    dc        = src.dc;           sz        = src.sz;          bold = src.bold;  italic = src.italic;
    underline = src.underline;    strikeout = src.strikeout;   face = src.face;
    }
  };


class FontMgr {
int                      stkX;
Expandable <FontAttr, 4> stk;

public:
FontAttr                 current;
LOGFONT                  curLogFont;

  FontMgr();
 ~FontMgr();

  void initialize(TCchar* face, int fontSize, CDC* dc);
  void pop();
  void setSize(int fontSize);
  void setBold();
  void setItalic();
  void setUnderLine();
  void setStrikeOut();

  FontAttr* getAttr()    {return &stk[stkX];}     // Returns a temporary pointer to the current attr
  LOGFONT&  getLogFont() {return curLogFont;}

private:

  FontAttr& push();
  void      install(FontAttr& attr, CFont& font);
  void      update(CFont& font, FontAttr& attr);
  void      createFailed(TCchar* fn);
  };

