// ICS_214aDoc.cpp : implementation of the ICS_214aDoc class


#include "stdafx.h"
#include "ICS_214aDoc.h"
#include "ICS_214a.h"
#include "Activity.h"
#include "ActvtyNameDlg.h"
#include "CopyFile.h"
#include "EditEntryDlg.h"
#include "EventLogDlg.h"
#include "filename.h"
#include "GetPathDlg.h"
#include "IniFile.h"
#include "MessageBox.h"
#include "NotePad.h"
#include "Options.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "StopEntryDlg.h"
#include "Utilities.h"


static TCchar* FileSection = _T("Files");
static TCchar* LogPath     = _T("LogPath");


// ICS_214aDoc

IMPLEMENT_DYNCREATE(ICS_214aDoc, CDocument)

BEGIN_MESSAGE_MAP(ICS_214aDoc, CDocument)
  ON_COMMAND(ID_NewLog,        &ICS_214aDoc::OnNewLog)
  ON_COMMAND(ID_FILE_OPEN,     &ICS_214aDoc::OnFileOpen)
  ON_COMMAND(ID_FILE_SAVE,     &ICS_214aDoc::onSave214)
  ON_COMMAND(ID_MakeExcelFile, &ICS_214aDoc::onSaveExcel)
  ON_COMMAND(ID_EditHeader,    &ICS_214aDoc::OnEditHeader)
  ON_COMMAND(ID_LogEntry,      &ICS_214aDoc::OnLogEntry)
  ON_COMMAND(ID_StopEntry,     &ICS_214aDoc::OnStopEntry)
  ON_COMMAND(ID_EditLogEntry,  &ICS_214aDoc::OnEditLogEntry)
  ON_COMMAND(ID_Options, &ICS_214aDoc::OnOptions)
END_MESSAGE_MAP()


// ICS_214aDoc construction/destruction

ICS_214aDoc::ICS_214aDoc() noexcept {
//  saveAsTitle = _T("eICS-214a");
  defExt = _T("214");   defFilePat = _T("*.214");
  }


void ICS_214aDoc::OnOptions() {
OptionsDlg dlg;

  dlg.excelOne = options.excelOne;

  if (dlg.DoModal() == IDOK) {
    options.excelOne = dlg.excelOne;
    }
  }


void ICS_214aDoc::OnNewLog() {
String path;
String title = _T("Specify New Log Name");

  activity.clear();   notePad.clear();   defFileName.clear();   OnNewDocument();


  if (!getSaveAsPathDlg(title, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  activity.setStoreAll();   onSaveDocument(path, true);

  iniFile.writeString(FileSection, LogPath, path);

  OnEditHeader();
  }



void ICS_214aDoc::OnFileOpen() {
String path;
String title = _T("Specify Existing Log File");

  activity.clear();   notePad.clear();

  iniFile.readString(FileSection, LogPath, defFileName);

  if (!getPathDlg(title, defFileName, defExt, defFilePat, path)) return;

  defFileName = getMainName(path);

  iniFile.writeString(FileSection, LogPath, path);

  notePad.clear();

  if (OnOpenDocument(path)) {backupCopy(path, 10);   invalidate();}
  }


String& ICS_214aDoc::getDefFileName()
                          {iniFile.readString(FileSection, LogPath, defFileName);  return defFileName;}


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


void ICS_214aDoc::OnLogEntry() {
EventLogDlg dlg;

  dlg.logDate   = getDateNow();
  dlg.startTime = getTimeNow();

  if (dlg.DoModal() == IDOK) {
    activity.add(dlg.logDate, dlg.startTime, dlg.endTime, dlg.logActivity);

    activity.setStoreIncr();   reOpenDocument();

    invalidate();
    }
  }


void ICS_214aDoc::OnStopEntry() {
StopEntryDlg dlg;

  dlg.stopDate = getDateNow();
  dlg.stopTime = getTimeNow();

  if (dlg.DoModal() == IDOK) {

    activity.setStoreAll();   DoFileSave();

    invalidate();
    }
  }


void ICS_214aDoc::OnEditLogEntry() {
EditEntryDlg dlg;

  if (dlg.DoModal() == IDOK) {

    activity.setStoreAll();   DoFileSave();

    invalidate();
    }
  }


void ICS_214aDoc::onSave214() {
String path;
String title = _T("Save Log Data File");

  if (!getSaveAsPathDlg(title, defFileName, defExt, defFilePat, path)) return;

  iniFile.writeString(FileSection, LogPath, path);

  activity.setStoreAll();   saveDoc(path);

  }


void ICS_214aDoc::onSaveExcel() {
String path;
String title = _T("Save Excel CSV File");

  if (!getSaveAsPathDlg(title, defFileName, _T("csv"), _T("*.csv"), path)) return;

  activity.setStoreExcel();   saveDoc(path);
  }


void ICS_214aDoc::saveDoc(String& path) {
String name;
String s;

  if (!onSaveDocument(path, true)) {
    name = removePath(path);   s.format(_T("Unable to Open File: %s"), name.str());
    messageBox(s);
    }
  }


// ICS_214aDoc serialization

void ICS_214aDoc::serialize(Archive& ar) {

  if (ar.isStoring()) {activity.store(ar); return;}

  activity.load(ar);
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

