// EventLogDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EventLogDlg.h"
#include "Date.h"
#include "Resource.h"



BEGIN_MESSAGE_MAP(EventLogDlg, CDialogEx)
  ON_EN_CHANGE(IDC_LogDate,   &EventLogDlg::OnChangeLogdate)
  ON_EN_CHANGE(IDC_StartTime, &EventLogDlg::OnChangeStarttime)
  ON_EN_CHANGE(IDC_EndTime,   &EventLogDlg::OnChangeEndtime)
END_MESSAGE_MAP()


// EventLogDlg dialog

IMPLEMENT_DYNAMIC(EventLogDlg, CDialogEx)

EventLogDlg::EventLogDlg(CWnd* pParent) : CDialogEx(IDD_EventLogEntry, pParent), logDate(_T("")),
                        startTime(_T("")), endTime(_T("")), logActivity(_T("")) { }

EventLogDlg::~EventLogDlg() { }


void EventLogDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LogDate,     logDateCtrl);
  DDX_Text(   pDX, IDC_LogDate,     logDate);
  DDX_Control(pDX, IDC_StartTime,   startTimeCtrl);
  DDX_Text(   pDX, IDC_StartTime,   startTime);
  DDX_Control(pDX, IDC_EndTime,     endTimeCtrl);
  DDX_Text(   pDX, IDC_EndTime,     endTime);
  DDX_Text(   pDX, IDC_LogActivity, logActivity);
  }


// EventLogDlg message handlers


void EventLogDlg::OnChangeLogdate()   {Date::onChangeDate(logDateCtrl);}
void EventLogDlg::OnChangeStarttime() {Date::onChangeTime(startTimeCtrl);}
void EventLogDlg::OnChangeEndtime()   {Date::onChangeTime(endTimeCtrl);}
