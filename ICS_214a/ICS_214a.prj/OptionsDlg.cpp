// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OptionsDlg.h"


// OptionsDlg dialog

IMPLEMENT_DYNAMIC(OptionsDlg, CDialogEx)


OptionsDlg::OptionsDlg(CWnd* pParent) : CDialogEx(IDD_Options, pParent), excelOne(FALSE) { }


OptionsDlg::~OptionsDlg() { }


void OptionsDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Check(pDX, IDC_ExcelOne, excelOne);
  }


BEGIN_MESSAGE_MAP(OptionsDlg, CDialogEx)
END_MESSAGE_MAP()
