// ActvtyNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ActvtyNameDlg.h"
#include "Date.h"


// ActvtyNameDlg dialog

IMPLEMENT_DYNAMIC(ActvtyNameDlg, CDialogEx)

ActvtyNameDlg::ActvtyNameDlg(CWnd* pParent) : CDialogEx(IDD_ActvtyName, pParent), name(_T("")),
                                  prepDate(_T("")), leaderName(_T("")), leaderPosition(_T("")),
                                  opPeriod(_T("")), prepBy(_T("")), missionNo(_T("")),
                                  prepTime(_T("")), updateTime(false), updateDate(false) { }


ActvtyNameDlg::~ActvtyNameDlg() { }


void ActvtyNameDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(   pDX, IDC_IncidentName,    name);
  DDX_Control(pDX, IDC_PrepDate,        prepDateCtrl);
  DDX_Text(   pDX, IDC_PrepDate,        prepDate);
  DDX_Control(pDX, IDC_PrepTime,        prepTimeCtrl);
  DDX_Text(   pDX, IDC_PrepTime,        prepTime);
  DDX_Text(   pDX, IDC_LeaderName,      leaderName);
  DDX_Text(   pDX, IDC_LeaderPosition,  leaderPosition);
  DDX_Text(   pDX, IDC_OperationPeriod, opPeriod);
  DDX_Text(   pDX, IDC_PreparedBy,      prepBy);
  DDX_Text(   pDX, IDC_MissionNumber,   missionNo);
  }


BEGIN_MESSAGE_MAP(ActvtyNameDlg, CDialogEx)
  ON_EN_CHANGE(IDC_PrepDate, &ActvtyNameDlg::OnChangePrepdate)
  ON_EN_CHANGE(IDC_PrepTime, &ActvtyNameDlg::OnChangePreptime)
END_MESSAGE_MAP()


void ActvtyNameDlg::OnChangePrepdate() {Date::onChangeDate(prepDateCtrl);}


void ActvtyNameDlg::OnChangePreptime() {Date::onChangeTime(prepTimeCtrl);}
