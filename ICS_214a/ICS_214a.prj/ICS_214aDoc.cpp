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
#include "IniFile.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "Resource.h"
#include "Utilities.h"


static TCchar* FileSection = _T("Files");
static TCchar* LogPath     = _T("LogPath");


// ICS_214aDoc

IMPLEMENT_DYNCREATE(ICS_214aDoc, CDocument)

BEGIN_MESSAGE_MAP(ICS_214aDoc, CDocument)
  ON_COMMAND(ID_EditHeader,    &OnEditHeader)
  ON_COMMAND(ID_LogEntry,      &OnLogEntry)
  ON_COMMAND(ID_StopEntry,     &OnStopEntry)
  ON_COMMAND(ID_EditLogEntry,  &OnEditLogEntry)
  ON_COMMAND(ID_NewLog,        &OnNewLog)
  ON_COMMAND(ID_FILE_OPEN,     &OnFileOpen)
  ON_COMMAND(ID_MakeExcelFile, &onSaveExcel)
  ON_COMMAND(ID_FILE_SAVE,     &onSave214)
  ON_COMMAND(ID_Options,       &OnOptions)
  ON_COMMAND(ID_CalibDspPrt,   &OnCalibDspPrt)
END_MESSAGE_MAP()


// ICS_214aDoc construction/destruction

ICS_214aDoc::ICS_214aDoc() noexcept {
//  saveAsTitle = _T("eICS-214a");
  defExt = _T("214");   defFilePat = _T("*.214");
  }


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
String path;
String title = _T("Specify New Log Name");

  activity.clear();   notePad.clear();   defFileName.clear();   OnNewDocument();

  if (!getSaveAsPathDlg(title, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  dataSource = ActivitySrc;   onSaveDocument(path, true);

  iniFile.writeString(FileSection, LogPath, path);

  OnEditHeader();   display(ActivitySrc);
  }



void ICS_214aDoc::OnFileOpen() {
String path;
String title = _T("Specify Existing Log File");

  notePad.clear();   activity.clear();   dataSource = ActivitySrc;

  iniFile.readString(FileSection, LogPath, defFileName);

  if (!getPathDlg(title, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  iniFile.writeString(FileSection, LogPath, path);

  notePad.clear();

  if (OnOpenDocument(path)) {backupCopy(path, 10);   display(ActivitySrc);}
  }


String& ICS_214aDoc::getDefFileName()
                          {iniFile.readString(FileSection, LogPath, defFileName);  return defFileName;}


void ICS_214aDoc::onSave214() {
String path;
String title = _T("Save Log Data File");

  dataSource = ActivitySrc;

  if (!getSaveAsPathDlg(title, defFileName, defExt, defFilePat, path)) return;

  iniFile.writeString(FileSection, LogPath, path);

  saveDoc(path);
  }


void ICS_214aDoc::onSaveExcel() {
String path;
String title = _T("Save Excel CSV File");

  if (!getSaveAsPathDlg(title, defFileName, _T("csv"), _T("*.csv"), path)) return;

  dataSource = ExcelSrc;   saveDoc(path);
  }


void ICS_214aDoc::saveDoc(String& path) {
String name;
String s;

  if (!onSaveDocument(path, true)) {
    name = removePath(path);   s.format(_T("Unable to Open File: %s"), name.str());
    messageBox(s);
    }
  }


void ICS_214aDoc::OnOptions() {options();}


void ICS_214aDoc::OnCalibDspPrt() {CalibDspPrt calib;  calib();  display(NotePadSrc);}


void ICS_214aDoc::display(DataSource ds) {dataSource = ds; invalidate();}


// ICS_214aDoc serialization

void ICS_214aDoc::serialize(Archive& ar) {

  switch(ar.isStoring()) {
    case true:
      switch(dataSource) {
        case NotePadSrc   : notePad.archive(ar);     break;
        case ActivitySrc  : activity.storeAll(ar);   break;
        case IncrActvtySrc: activity.storeIncr(ar);  break;
        case ExcelSrc     : activity.storeExcel(ar); break;
        default         : return;
        }
      break;

    case false:
      switch(dataSource) {
        case ActivitySrc: activity.load(ar); break;
        }
      break;
    }
#if 0
  if (ar.isStoring()) {activity.store(ar); return;}

  activity.load(ar);
#endif
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


#if 0
EditEntryDlg dlg;

  if (dlg.DoModal() == IDOK) {

    activity.setStoreAll();
#endif
#if 0
EventLogDlg dlg;

  dlg.logDate   = getDateNow();
  dlg.startTime = getTimeNow();

  if (dlg.DoModal() == IDOK) {
    activity.add(dlg.logDate, dlg.startTime, dlg.endTime, dlg.logActivity);

    activity.setStoreIncr();
#endif
#if 0
StopEntryDlg dlg;

  dlg.stopDate = getDateNow();
  dlg.stopTime = getTimeNow();

  if (dlg.DoModal() == IDOK) {

    activity.setStoreAll();
#endif

