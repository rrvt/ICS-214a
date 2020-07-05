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
LogData* ld    = activity.entry(index);      if (!ld)       return;
String   date;
String   timeIn;
String   dateOut;
String   timeOut;
String   dsc;

  ld->get(date, timeIn, dateOut, timeOut, dsc);

  logDate = date;    logDateCtrl.SetWindowText(logDate);
  logTime = timeIn;  logTimeCtrl.SetWindowText(timeIn);
  endDate = dateOut; endDateCtrl.SetWindowText(endDate);
  endTime = timeOut; endTimeCtrl.SetWindowText(endTime);
  desc    = dsc;     descCtrl.SetWindowText(dsc);
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
  ON_CBN_SELCHANGE(IDC_EntryDesc,  &EditEntryDlg::onSelectEntry)
  ON_BN_CLICKED(  IDOK,            &EditEntryDlg::OnOk)
  ON_EN_CHANGE(   IDC_LogDate,     &EditEntryDlg::OnChangeLogdate)
  ON_EN_CHANGE(   IDC_StartTime,   &EditEntryDlg::OnChangeStarttime)
  ON_EN_CHANGE(   IDC_EndDate,     &EditEntryDlg::OnChangeEnddate)
  ON_EN_CHANGE(   IDC_EndTime,     &EditEntryDlg::OnChangeEndtime)
  ON_EN_KILLFOCUS(IDC_LogDate,     &EditEntryDlg::OnLeaveLogdate)
  ON_EN_KILLFOCUS(IDC_StartTime,   &EditEntryDlg::OnLeaveStarttime)
  ON_EN_KILLFOCUS(IDC_EndDate,     &EditEntryDlg::OnLeaveEnddate)
  ON_EN_KILLFOCUS(IDC_EndTime,     &EditEntryDlg::OnLeaveEndtime)
  ON_EN_KILLFOCUS(IDC_LogActivity, &EditEntryDlg::OnLeaveLogactivity)
END_MESSAGE_MAP()


void EditEntryDlg::OnChangeLogdate()   {Date::onChangeDate(logDateCtrl);}
void EditEntryDlg::OnChangeStarttime() {Date::onChangeTime(logTimeCtrl);}
void EditEntryDlg::OnChangeEnddate()   {Date::onChangeDate(endDateCtrl);}
void EditEntryDlg::OnChangeEndtime()   {Date::onChangeTime(endTimeCtrl);}


void EditEntryDlg::OnLeaveLogdate()     {logDateCtrl.GetWindowText(logDate); updateRcd();}
void EditEntryDlg::OnLeaveStarttime()   {logTimeCtrl.GetWindowText(logTime); updateRcd();}
void EditEntryDlg::OnLeaveEnddate()     {endDateCtrl.GetWindowText(endDate); updateRcd();}
void EditEntryDlg::OnLeaveEndtime()     {endTimeCtrl.GetWindowText(endTime); updateRcd();}
void EditEntryDlg::OnLeaveLogactivity() {descCtrl.GetWindowText(desc);       updateRcd();}
void EditEntryDlg::OnOk()               {CDialogEx::OnOK();                  updateRcd();}


void EditEntryDlg::updateRcd() {
int      index = entryDescCtrl.GetCurSel();  if (index < 0) return;
LogData* ld    = activity.entry(index);      if (!ld)       return;

  ld->set(logDate, logTime, endDate, endTime, desc);
  }

