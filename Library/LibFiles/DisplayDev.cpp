// Display Device Data


#include "stdafx.h"
#include "DisplayDev.h"




void DisplayDev::initialize() {note = 0; lastPageNo = 0; lastLeftMargin = 0; endDoc = debugging = false;}



void DisplayDev::startDev() {
  note = notePadLp.start(); dev.noPages = 0; lastPageNo = 0; lastLeftMargin = 0;
  endDoc = debugging = false;
  }


  // Output to Device (Display or Printer)

void DisplayDev::operator() () {
bool endLoop = false;

  for ( ; note && !endLoop; note = notePadLp.nextNode()) {

    if (note->beginLine)     dev << dBeginLine; if (dev.isEndPage()) break;
    if (note->leftMargin != lastLeftMargin)
                            {dev << dSetLMargin(note->leftMargin); lastLeftMargin = note->leftMargin;}
    if (note->clrTabs)       dev << dClrTabs;
    if (note->tabValue)      dev << dSetTab(note->tabValue);
    if (note->rTabValue)     dev << dSetRTab(note->rTabValue);

    if (note->fSize)         {dev << dFSize(note->fSize);       if (dev.isEndPage()) break;}
    if (note->prevFont)      {dev << dPrevFont;                 if (dev.isEndPage()) break;}
    if (note->bold)          {dev << dBoldFont;                 if (dev.isEndPage()) break;}
    if (note->italic)        {dev << dItalicFont;               if (dev.isEndPage()) break;}
    if (note->underline)     {dev << dUnderLineFont;            if (dev.isEndPage()) break;}
    if (note->strikeOut)     {dev << dStrikeOutFont;            if (dev.isEndPage()) break;}

    if (note->tab == true)   {dev << dTab;                      if (dev.isEndPage()) break;}
    if (note->center)        {dev << dCenter;                   if (dev.isEndPage()) break;}
    if (note->right)         {dev << dRight;                    if (dev.isEndPage()) break;}

    if (note->editBoxX >= 0) {dev << dEditBox(note->editBoxX);  if (dev.isEndPage()) break;}

                              dev << note->line;                if (dev.isEndPage()) break;

    if (note->endLine)       {dev << dEndLine;                  if (dev.isEndPage()) break;}

    if (note->crlf)          {dev << dCrlf;                     if (dev.isEndPage()) break;}

    if (note->endPage)       {dev << dEndPage;                  endLoop = true;}

    if (note->debug)         debugging = true;
    }

  endDoc = note == 0;
  }


#if 0
void DisplayDev::skipPage() {
bool endLoopNow = false;

  for (; note && !endLoopNow; note = notePadLp.nextNode()) {
    if (note->fSize)    dev.setFontSize(note->fSize);

    if (note->prevFont) dev.setPrevFont();

    if (note->crlf)     {dev.crlf();    if (dev.isEndPage()) endLoopNow = true;}

    if (note->endPage)  {if (dev.isEndPage()) endLoopNow = true;}
    }

  endDoc = note == 0;
  }

#endif
