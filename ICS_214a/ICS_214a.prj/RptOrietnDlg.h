// Set Report Printer Orientation


#pragma once
#include "Resource.h"
#include "PrintMgr.h"


class RptOrietnDlg : public CDialogEx {

  DECLARE_DYNAMIC(RptOrietnDlg)

public:
Cstring    ntpd;
Cstring    acty;
CComboBox  ntpdCtl;
CComboBox  actyCtl;

               RptOrietnDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual     ~RptOrietnDlg();

  virtual BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Orientation };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void initOrietn(CComboBox& ctl, Cstring& orietn);
  };
