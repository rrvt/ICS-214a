// Font Manager
// Copyright Software Design & Engineering, Robert R. Van Tuyl, 2013.  All rights reserved.


#include "stdafx.h"
#include "FontMgr.h"
#include "MessageBox.h"


FontMgr::FontMgr() : stkX(0), current() { }

FontMgr::~FontMgr() {
  while (stkX > 0) pop();
  }


void FontMgr::initialize(TCchar* face, int fontSize, CDC* dc) {
CFont   font;
CFont*  original;
LOGFONT logFont;

  stkX = 0;   dc->SetMapMode(MM_TEXT);

  if (!font.CreatePointFont(fontSize, face, dc)) {createFailed(_T("initialize")); return;}

  original = dc->SelectObject(&font);    font.GetLogFont(&curLogFont);

  if (original) {
    original->GetLogFont(&logFont);    original->DeleteObject();

    FontAttr& attr = stk[stkX];
    attr.dc        = dc;
    attr.sz        = logFont.lfHeight;
    attr.bold      = logFont.lfWeight == FW_BOLD;
    attr.italic    = logFont.lfItalic;
    attr.underline = logFont.lfUnderline;
    attr.strikeout = logFont.lfStrikeOut;
    attr.face      = logFont.lfFaceName;
    }


  FontAttr& attr = stk[++stkX];
  attr.dc   = dc;
  attr.sz   = fontSize;
  attr.face = face;         current = attr;
  }


void FontMgr::setSize(int fontSize) {
FontAttr& attr = push();
CFont     font;

  attr.sz = fontSize;

  if (!font.CreatePointFont(attr.sz, attr.face, attr.dc)) {createFailed(_T("setSize")); return;}

  update(font, attr);
  }



void FontMgr::setBold() {
FontAttr& attr = push();
CFont     font;

  if (!font.CreatePointFont(attr.sz, attr.face, attr.dc)) {createFailed(_T("setBold")); return;}

  attr.bold = true;  update(font, attr);
  }



void FontMgr::setItalic() {
FontAttr& attr = push();
CFont     font;

  if (!font.CreatePointFont(attr.sz, attr.face, attr.dc)) {createFailed(_T("setItalic")); return;}

  attr.italic = true;   update(font, attr);
  }



void FontMgr::setUnderLine() {
FontAttr& attr = push();
CFont     font;

  if (!font.CreatePointFont(attr.sz, attr.face, attr.dc)) {createFailed(_T("setUnderLine")); return;}

  attr.underline = true;   update(font, attr);
  }



void FontMgr::setStrikeOut() {
FontAttr& attr = push();
CFont     font;

  if (!font.CreatePointFont(attr.sz, attr.face, attr.dc)) {createFailed(_T("setStrikeOut")); return;}

  attr.strikeout = true;   update(font, attr);
  }


FontAttr& FontMgr::push() {FontAttr& attr = stk[++stkX]; attr = stk[stkX-1]; return attr;}


void FontMgr::pop() {
          if (stkX <= 0) return;
FontAttr& attr = stk[--stkX];
CFont     font;

  if (!font.CreatePointFont(attr.sz, attr.face, attr.dc)) {createFailed(_T("pop")); return;}

  update(font, attr);
  }



void FontMgr::update(CFont& font, FontAttr& attr) {
LOGFONT logFont;
CFont   f;

  font.GetLogFont(&logFont); font.DeleteObject();

                      logFont.lfHeight    = attr.sz;
  if (attr.bold)      logFont.lfWeight    = FW_BOLD;
  if (attr.italic)    logFont.lfItalic    = -1;
  if (attr.underline) logFont.lfUnderline = true;
  if (attr.strikeout) logFont.lfStrikeOut = true;

  if (!f.CreatePointFontIndirect(&logFont, attr.dc)) {createFailed(_T("update")); return; }

  install(attr, f);
  }


void FontMgr::install(FontAttr& attr, CFont& font) {
CFont* x;

  font.GetLogFont(&curLogFont);

  x = attr.dc->SelectObject(&font);   if (x) x->DeleteObject();   current = attr;
  }


void FontMgr::createFailed(TCchar* fn)
                            {String s;   s.format(_T("Create Font failed in %s"), fn);   messageBox(s);}


