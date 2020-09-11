// StopEntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StopEntryDlg.h"
#include "Activity.h"
#include "Date.h"
#include "Utilities.h"


// StopEntryDlg dialog

IMPLEMENT_DYNAMIC(StopEntryDlg, CDialogEx)


BEGIN_MESSAGE_MAP(StopEntryDlg, CDialogEx)
  ON_BN_CLICKED(  IDOK,         &StopEntryDlg::OnOk)
  ON_EN_CHANGE(   IDC_StopDate, &StopEntryDlg::OnChangeStopdate)
  ON_EN_CHANGE(   IDC_StopTime, &StopEntryDlg::OnChangeStoptime)
  ON_EN_KILLFOCUS(IDC_StopDate, &StopEntryDlg::OnLeaveStopdate)
  ON_EN_KILLFOCUS(IDC_StopTime, &StopEntryDlg::OnLeaveStoptime)
END_MESSAGE_MAP()


StopEntryDlg::StopEntryDlg(CWnd* pParent) : CDialogEx(IDD_StopEntry, pParent), entryDesc(_T("")),
                                                                  stopDate(_T("")), stopTime(_T("")) { }

StopEntryDlg::~StopEntryDlg() { }


BOOL StopEntryDlg::OnInitDialog() {
ActyIter iter(activity);
LogData* ld;
int      i;
String   s;
String   date;
String   timeIn;
String   dateOut;
String   timeOut;
String   desc;

  CDialogEx::OnInitDialog();

  for (ld = iter(), i = 0; ld; ld = iter++, i++) {
    ld->get(date, timeIn, dateOut, timeOut, desc);
    if (timeOut.isEmpty()) {
      s = addTab(date, 10);  s += addTab(timeIn, 8);    s += desc;

      entryDescCtrl.AddString(s);   indexes += i;
      }
    }

  if (indexes.end()) entryDescCtrl.SetCurSel(0);   return TRUE;
  }


void StopEntryDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control( pDX, IDC_EntryDesc, entryDescCtrl);
  DDX_CBString(pDX, IDC_EntryDesc, entryDesc);
  DDX_Control( pDX, IDC_StopDate,  stopDateCtrl);
  DDX_Text(    pDX, IDC_StopDate,  stopDate);
  DDX_Control( pDX, IDC_StopTime,  stopTimeCtrl);
  DDX_Text(    pDX, IDC_StopTime,  stopTime);
  }


void StopEntryDlg::OnChangeStopdate() {Date::onChangeDate(stopDateCtrl);}
void StopEntryDlg::OnChangeStoptime() {Date::onChangeTime(stopTimeCtrl);}


void StopEntryDlg::OnLeaveStopdate() {stopDateCtrl.GetWindowText(stopDate); updateRcd();}
void StopEntryDlg::OnLeaveStoptime() {stopTimeCtrl.GetWindowText(stopTime); updateRcd();}
void StopEntryDlg::OnOk()            {CDialogEx::OnOK();                    updateRcd();}


void StopEntryDlg::updateRcd() {
int      index = entryDescCtrl.GetCurSel();  if (index < 0 || indexes.end() <= index) return;
int      selX  = indexes[index];
LogData* ld    = activity.entry(selX);       if (!ld)                                 return;

  ld->setStop(stopDate, stopTime);  ld->archived = false;
  }

