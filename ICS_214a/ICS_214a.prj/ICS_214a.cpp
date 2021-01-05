// ICS_214a.cpp : Defines the class behaviors for the application.


#include "stdafx.h"
#include "ICS_214a.h"
#include "About.h"
#include "ICS_214aDoc.h"
#include "ICS_214aView.h"
#include "IniFile.h"
#include "Options.h"
#include "NotePad.h"
#include "MainFrame.h"


ICS_214a theApp;                       // The one and only ICS_214a object
IniFile iniFile;


// ICS_214a

BEGIN_MESSAGE_MAP(ICS_214a, CWinAppEx)
  ON_COMMAND(ID_APP_ABOUT,        &ICS_214a::OnAppAbout)
  ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
  ON_COMMAND(ID_Help,             &ICS_214a::OnHelp)
END_MESSAGE_MAP()


// ICS_214a initialization

BOOL ICS_214a::InitInstance() {

  CWinAppEx::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  notePad.clear();

  SetRegistryKey(appID);

  LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

  // Register the application's document templates.  Document templates
  // serve as the connection between documents, frame windows and views

  CSingleDocTemplate* pDocTemplate;

  pDocTemplate = new CSingleDocTemplate(
    IDR_MAINFRAME,
    RUNTIME_CLASS(ICS_214aDoc),
    RUNTIME_CLASS(MainFrame),       // main SDI frame window
    RUNTIME_CLASS(ICS_214aView));

  if (!pDocTemplate) return FALSE;

  AddDocTemplate(pDocTemplate);

  // Parse command line for standard shell commands, DDE, file open

  CCommandLineInfo cmdInfo;   ParseCommandLine(cmdInfo);

  // Dispatch commands specified on the command line.  Will return FALSE if
  // app was launched with /RegServer, /Register, /Unregserver or /Unregister.

  if (!ProcessShellCommand(cmdInfo)) return FALSE;

  setAppName(_T("eICS-214a")); setTitle(_T("Event Log"));

  view()->setFont(_T("Arial"), 12.0);

  options.load();

  if (doc()->getDefFileName().isEmpty()) doc()->OnNewLog();
  else                                   doc()->OnFileOpen();

  m_pMainWnd->ShowWindow(SW_SHOW);   m_pMainWnd->UpdateWindow();   return TRUE;
  }


void ICS_214a::OnHelp() {
String topic = m_pszHelpFilePath; topic += _T(">Introduction");

  ::HtmlHelp(m_pMainWnd->m_hWnd, topic,  HH_DISPLAY_TOC, 0);
  }


void ICS_214a::OnAppAbout() {CAboutDlg aboutDlg; aboutDlg.DoModal();}


