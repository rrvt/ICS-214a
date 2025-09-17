// ICS_214aDoc.cpp : implementation of the ICS_214aDoc class


#include "stdafx.h"
#include "ICS_214aDoc.h"
#include "Activity.h"
#include "ActvtyNameDlg.h"
#include "CalibDspPrt.h"
#include "CopyFile.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "ICS_214a.h"
#include "ICS_214aView.h"
#include "IniFileEx.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Resource.h"
#include "Utilities.h"


static TCchar* FileSection = _T("Files");
static TCchar* LogPath     = _T("LogPath");


// ICS_214aDoc

IMPLEMENT_DYNCREATE(ICS_214aDoc, CDocument)

BEGIN_MESSAGE_MAP(ICS_214aDoc, CDocument)
  ON_COMMAND(ID_EditHeader,     &OnEditHeader)
  ON_COMMAND(ID_LogEntry,       &OnLogEntry)
  ON_COMMAND(ID_StopEntry,      &OnStopEntry)
  ON_COMMAND(ID_EditLogEntry,   &OnEditLogEntry)
  ON_COMMAND(ID_NewLog,         &OnNewLog)
  ON_COMMAND(ID_FILE_OPEN,      &OnFileOpen)

  ON_COMMAND(ID_MakeExcelMenu,  &onSaveExcel)
  ON_COMMAND(ID_MakeExcelFile,  &onSaveExcel)
  ON_COMMAND(ID_MakeExcelFile2, &onSaveExcel2)

  ON_COMMAND(ID_FILE_SAVE,      &onSave214)
  ON_COMMAND(ID_CalibDspPrt,    &OnCalibDspPrt)
END_MESSAGE_MAP()


// ICS_214aDoc construction/destruction

ICS_214aDoc::ICS_214aDoc() noexcept { }


void ICS_214aDoc::OnEditHeader() {
ActvtyNameDlg dlg;

  if (activity.prepDate.isEmpty()) {activity.prepDate = getDateNow();}
  if (activity.prepTime.isEmpty()) {activity.prepTime = getTimeNow();}

  dlg.name           = activity.name;
  dlg.prepDate       = activity.prepDate;
  dlg.prepTime       = activity.prepTime;
  dlg.leaderName     = activity.leaderName;
  dlg.leaderPosition = activity.leaderPosition;
  dlg.opPeriod       = activity.operationalPeriod;
  dlg.prepBy         = activity.preparedBy;
  dlg.missionNo      = activity.missionNo;

  if (dlg.DoModal() == IDOK) {
    activity.name               = dlg.name;
    activity.prepDate           = dlg.prepDate;
    activity.prepTime           = dlg.prepTime;
    activity.leaderName         = dlg.leaderName;
    activity.leaderPosition     = dlg.leaderPosition;
    activity.operationalPeriod  = dlg.opPeriod;
    activity.preparedBy         = dlg.prepBy;
    activity.missionNo          = dlg.missionNo;

    if (!DoFileSave()) onSave214();
    }

  invalidate();
  }


void ICS_214aDoc::OnLogEntry()
  {if (activity.logEntry())     {dataSource = IncrActvtySrc; reOpenDocument();   invalidate();}}

void ICS_214aDoc::OnStopEntry()
  {if (activity.stopEntry())    {dataSource = ActivitySrc;   DoFileSave();        invalidate();}}

void ICS_214aDoc::OnEditLogEntry()
  {if (activity.editLogEntry()) {dataSource = ActivitySrc;   DoFileSave();        invalidate();}}


void ICS_214aDoc::OnNewLog() {
PathDlgDsc dsc;

  activity.clear();   notePad.clear();   OnNewDocument();

  dsc(_T("Specify New Log Name"), 0, _T("214"), _T("*.214"));

  if (!setSaveAsPath(dsc)) return;

  dataSource = ActivitySrc;   onSaveDocument(path);

  iniFile.writeString(FileSection, LogPath, path);

  OnEditHeader();   display(ActivitySrc);
  }



void ICS_214aDoc::OnFileOpen() {
PathDlgDsc dsc;

  notePad.clear();   activity.clear();   dataSource = ActivitySrc;

  iniFile.readString(FileSection, LogPath, path);

  dsc(_T("Specify Existing Log File"), path, _T("214"), _T("*.214"));   if (!setOpenPath(dsc)) return;

  iniFile.writeString(FileSection, LogPath, path);

  notePad.clear();

  if (OnOpenDocument(path)) {backupCopy(path, 10);   display(ActivitySrc);}
  }


void ICS_214aDoc::onSave214() {
PathDlgDsc dsc;

  dataSource = ActivitySrc;

  dsc(_T("Save Log Data File"), path, _T("214"), _T("*.214"));   if (!setSaveAsPath(dsc)) return;

  iniFile.writeString(FileSection, LogPath, path);

  saveDoc(path);
  }


void ICS_214aDoc::onSaveExcel() {
PathDlgDsc dsc;
String     stk = path;
String     name = getMainName(path);

  dsc(_T("Save Excel CSV File"), name, _T("csv"), _T("*.csv"));   if (!setSaveAsPath(dsc)) return;

  dataSource = ExcelSrc;   saveDoc(path);   path = stk;
  }


void ICS_214aDoc::onSaveExcel2() {
PathDlgDsc dsc;
String     stk = path;
String     name = getMainName(path);

  dsc(_T("Save Excel CSV File"), name, _T("csv"), _T("*.csv"));   if (!setSaveAsPath(dsc)) return;

  dataSource = ExcelSrc2;   saveDoc(path);   path = stk;
  }


void ICS_214aDoc::saveDoc(String& path) {
String name;
String s;

  if (!onSaveDocument(path))
        {name = removePath(path);   s.format(_T("Unable to Open File: %s"), name.str());   messageBox(s);}
  }


void ICS_214aDoc::OnCalibDspPrt() {CalibDspPrt calib;  calib();  display(NotePadSrc);}


void ICS_214aDoc::display(DataSource ds) {dataSource = ds; invalidate();}


// ICS_214aDoc serialization

void ICS_214aDoc::serialize(Archive& ar) {

  switch(ar.isStoring()) {
    case true:
      switch(dataSource) {
        case NotePadSrc   : ar << notePad;                  break;
        case ActivitySrc  : activity.storeAll(ar);          break;
        case IncrActvtySrc: activity.storeIncr(ar);         break;
        case ExcelSrc     : activity.storeExcel(ar, false); break;
        case ExcelSrc2    : activity.storeExcel(ar, true);  break;
        default           : return;
        }
      break;

    case false:
      switch(dataSource) {
        case ActivitySrc: activity.load(ar); break;
        }
      break;
    }
  }


// ICS_214aDoc diagnostics

#ifdef _DEBUG
void ICS_214aDoc::AssertValid() const
{
  CDocument::AssertValid();
}

void ICS_214aDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG


