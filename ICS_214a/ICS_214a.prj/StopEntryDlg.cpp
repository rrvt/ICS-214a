// StopEntryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StopEntryDlg.h"
#include "Activity.h"
#include "Date.h"
#include "Utilities.h"


// StopEntryDlg dialog

IMPLEMENT_DYNAMIC(StopEntryDlg, CDialogEx)


StopEntryDlg::StopEntryDlg(CWnd* pParent) : CDialogEx(IDD_StopEntry, pParent), entryDesc(_T("")),
                                                                  stopDate(_T("")), stopTime(_T("")) { }

StopEntryDlg::~StopEntryDlg() { }


BOOL StopEntryDlg::OnInitDialog() {
ActivityIter iter(activity);
LogData*     ld;
int          i;
String       s;
String       date;
String       timeIn;
String       dateOut;
String       timeOut;
String       desc;


  CDialogEx::OnInitDialog();

  for (ld = iter(), i = 0; ld; ld = iter++, i++) {
    ld->get(date, timeIn, dateOut, timeOut, desc);
    if (timeOut.isEmpty()) {
      s = addTab(date, 10);  s += addTab(timeIn, 8);    s += desc;

      entryDescCtrl.AddString(s);   indexes[indexes.end()] = i;
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


BEGIN_MESSAGE_MAP(StopEntryDlg, CDialogEx)
  ON_BN_CLICKED(IDOK, &StopEntryDlg::OnOk)
  ON_EN_CHANGE(IDC_StopDate, &StopEntryDlg::OnChangeStopdate)
  ON_EN_CHANGE(IDC_StopTime, &StopEntryDlg::OnChangeStoptime)
END_MESSAGE_MAP()


void StopEntryDlg::OnOk() {
int      sel;
int      actX;
LogData* ld;
String   dtOut;

  CDialogEx::OnOK();

  sel = entryDescCtrl.GetCurSel();

  if (sel < indexes.end()) {
    actX = indexes[sel];
    ld = activity.entry(actX);
    if (ld) {ld->setStop(stopDate, stopTime);  ld->archived = false;}
    }
  }
