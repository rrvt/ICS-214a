// Global Options


#include "stdafx.h"
#include "Options.h"
#include "IniFile.h"
#include "OptionsDlg.h"


static TCchar* Section = _T("Options");
static TCchar* Orientation    = _T("Orientation");
static TCchar* ExcelOneKey    = _T("ExcelOne");
static TCchar* TopMarginKey   = _T("TopMargin");
static TCchar* LeftMarginKey  = _T("LeftMargin");
static TCchar* RightMarginKey = _T("RightMargin");
static TCchar* BotMarginKey   = _T("BotMargin");

Options options;


void Options::operator() () {
OptionsDlg dlg;

  load();

  dlg.orient       = orient == Portrait ? PortraitKey : LandscapeKey;
  dlg.topMargin    = topMargin;
  dlg.leftMargin   = leftMargin;
  dlg.rightMargin  = rightMargin;
  dlg.botMargin    = botMargin;

  if (dlg.DoModal() == IDOK) {
    String s = dlg.orient;

    orient       = s == LandscapeKey ? Landscape : Portrait;
    topMargin    = dlg.topMargin;
    leftMargin   = dlg.leftMargin;
    rightMargin  = dlg.rightMargin;
    botMargin    = dlg.botMargin;

    store();
    }
  }


void Options::load() {
String excel;

  orient = (PrtrOrient) iniFile.readInt(Section, Orientation, Portrait);
  iniFile.readString(Section, ExcelOneKey,    excel);      excelOne = excel == _T("1");
  iniFile.readString(Section, TopMarginKey,   topMargin,   _T("3.0"));
  iniFile.readString(Section, LeftMarginKey,  leftMargin,  _T("3.0"));
  iniFile.readString(Section, RightMarginKey, rightMargin, _T("3.0"));
  iniFile.readString(Section, BotMarginKey,   botMargin,   _T("3.0"));
  }


void Options::store() {
String excel = excelOne ? _T('1') : _T('0');

  iniFile.writeInt(   Section, Orientation,    orient);
  iniFile.writeString(Section, ExcelOneKey,    excel);
  iniFile.writeString(Section, TopMarginKey,   topMargin);
  iniFile.writeString(Section, LeftMarginKey,  leftMargin);
  iniFile.writeString(Section, RightMarginKey, rightMargin);
  iniFile.writeString(Section, BotMarginKey,   botMargin);
  }

