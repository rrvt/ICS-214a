// Stop Log Entry


#pragma once
#include "Expandable.h"
#include "Resource.h"


// StopEntryDlg dialog

class StopEntryDlg : public CDialogEx {

  DECLARE_DYNAMIC(StopEntryDlg)

public:

Expandable<int, 1> indexes;

CComboBox entryDescCtrl;
CString   entryDesc;
CEdit     stopDateCtrl;
CString   stopDate;
CEdit     stopTimeCtrl;
CString   stopTime;

           StopEntryDlg(CWnd* pParent = nullptr);
  virtual ~StopEntryDlg();

  virtual BOOL OnInitDialog();

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_StopEntry };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void updateRcd();

public:
  afx_msg void OnOk();
  afx_msg void OnChangeStopdate();
  afx_msg void OnChangeStoptime();
  afx_msg void OnLeaveStopdate();
  afx_msg void OnLeaveStoptime();
};
