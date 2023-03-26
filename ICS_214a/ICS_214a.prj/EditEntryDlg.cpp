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
ActyIter iter(activity);
Event*   event;
int      n;
String   s;

  CDialogEx::OnInitDialog();

  for (event = iter(), n = 0; event; event = iter++, n++) {

    s = addTab(event->startTime.getDate(), 10);   s += addTab(event->startTime.getHHMM(), 8);
    s += event->desc;

    entryDescCtrl.AddString(s);
    }

  if (n) entryDescCtrl.SetCurSel(n-1);   onSelectEntry();  return TRUE;
  }



void EditEntryDlg::onSelectEntry() {
int    index = entryDescCtrl.GetCurSel();  if (index < 0) return;
Event* event = activity.entry(index);      if (!event)       return;

  logDate = event->startTime.getDate();  logDateCtrl.SetWindowText(logDate);
  logTime = event->startTime.getHHMM();  logTimeCtrl.SetWindowText(logTime);
  endDate = event->endTime.getDate();    endDateCtrl.SetWindowText(endDate);
  endTime = event->endTime.getHHMM();    endTimeCtrl.SetWindowText(endTime);
  desc    = event->desc;                 descCtrl.SetWindowText(desc);
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
int    index = entryDescCtrl.GetCurSel();  if (index < 0) return;
Event* event    = activity.entry(index);      if (!event)       return;

  event->set(logDate, logTime, endDate, endTime, desc);
  }

