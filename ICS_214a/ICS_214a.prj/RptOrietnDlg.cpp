// RptOrietnDlg.cpp : implementation file
//

#include "pch.h"
#include "RptOrietnDlg.h"


IMPLEMENT_DYNAMIC(RptOrietnDlg, CDialogEx)

RptOrietnDlg::RptOrietnDlg(CWnd* pParent) :
                                       CDialogEx(IDD_Orientation, pParent), ntpd(_T("")), acty(_T("")) { }

RptOrietnDlg::~RptOrietnDlg() { }


BOOL RptOrietnDlg::OnInitDialog() {

  CDialogEx::OnInitDialog();

  initOrietn(ntpdCtl, ntpd);
  initOrietn(actyCtl, acty);

  return TRUE;
  }


void RptOrietnDlg::initOrietn(CComboBox& ctl, Cstring& orietn) {
  ctl.AddString(LandscapeKey);
  ctl.AddString(PortraitKey);
  ctl.SelectString(-1, orietn);
  }


void RptOrietnDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialogEx::DoDataExchange(pDX);
  DDX_Control( pDX, IDC_NtpdOrientn, ntpdCtl);
  DDX_CBString(pDX, IDC_NtpdOrientn, ntpd);
  DDX_Control( pDX, IDC_ActyOrientn, actyCtl);
  DDX_CBString(pDX, IDC_ActyOrientn, acty);
  }


BEGIN_MESSAGE_MAP(RptOrietnDlg, CDialogEx)
END_MESSAGE_MAP()

