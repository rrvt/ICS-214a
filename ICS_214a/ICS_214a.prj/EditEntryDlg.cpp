// EditEntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EditEntryDlg.h"
#include "Activity.h"
#include "Resource.h"
#include "Utilities.h"


// EditEntryDlg dialog

IMPLEMENT_DYNAMIC(EditEntryDlg, CDialogEx)

EditEntryDlg::EditEntryDlg(CWnd* pParent) : CDialogEx(IDD_EditEntry, pParent), logDate(_T("")),
                          logTime(_T("")), endTime(_T("")), desc(_T("")), endDate(_T("")) { }


EditEntryDlg::~EditEntryDlg() { }




BOOL EditEntryDlg::OnInitDialog() {
ActivityIter iter(activity);
LogData*     ld;
int          n;
String       s;
String       date;
String       timeIn;
String       dateOut;
String       timeOut;
String       desc;


  CDialogEx::OnInitDialog();

  for (ld = iter(), n = 0; ld; ld = iter++, n++) {

    ld->get(date, timeIn, dateOut, timeOut, desc);

    s = addTab(date, 10);  s += addTab(timeIn, 8);    s += desc;

    entryDescCtrl.AddString(s);
    }

  if (n) entryDescCtrl.SetCurSel(n-1);   onSelectEntry();  return TRUE;
  }



void EditEntryDlg::onSelectEntry() {
int      index = entryDescCtrl.GetCurSel();  if (index < 0) return;
LogData* ld    = activity.entry(index);    if (!ld)       return;
String   date;
String   timeIn;
String   dateOut;
String   timeOut;
String   desc;

  ld->get(date, timeIn, dateOut, timeOut, desc);

  logDateCtrl.SetWindowText(date);
  logTimeCtrl.SetWindowText(timeIn);
  endDateCtrl.SetWindowText(dateOut);
  endTimeCtrl.SetWindowText(timeOut);
     descCtrl.SetWindowText(desc);
  }


void EditEntryDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);

  DDX_Control(pDX, IDC_EntryDesc,   entryDescCtrl);
  DDX_Control(pDX, IDC_LogDate,     logDateCtrl);
  DDX_Text(   pDX, IDC_LogDate,     logDate);
  DDX_Control(pDX, IDC_StartTime,   logTimeCtrl);
  DDX_Text(   pDX, IDC_StartTime,   logTime);
  DDX_Control(pDX, IDC_EndDate,     endDateCtrl);
  DDX_Text(   pDX, IDC_EndDate,     endDate);
  DDX_Control(pDX, IDC_EndTime,     endTimeCtrl);
  DDX_Text(   pDX, IDC_EndTime,     endTime);
  DDX_Control(pDX, IDC_LogActivity, descCtrl);
  DDX_Text(   pDX, IDC_LogActivity, desc);
  }


BEGIN_MESSAGE_MAP(EditEntryDlg, CDialogEx)
  ON_CBN_SELCHANGE(IDC_EntryDesc, &EditEntryDlg::onSelectEntry)
  ON_BN_CLICKED(   IDOK,          &EditEntryDlg::OnOk)
END_MESSAGE_MAP()


// EditEntryDlg message handlers

void EditEntryDlg::OnOk() {
int      index;
LogData* ld;

  CDialogEx::OnOK();

  index = entryDescCtrl.GetCurSel();  if (index < 0) return;
  ld    = activity.entry(index);      if (!ld)       return;

  ld->set(logDate, logTime, endDate, endTime, desc);
  }
