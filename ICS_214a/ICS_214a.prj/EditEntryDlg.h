#pragma once


// EditEntryDlg dialog

class EditEntryDlg : public CDialogEx
{
  DECLARE_DYNAMIC(EditEntryDlg)

public:

CComboBox entryDescCtrl;
CEdit     logDateCtrl;
CString   logDate;
CEdit     logTimeCtrl;
CString   logTime;
CEdit     endDateCtrl;
CString   endDate;
CEdit     endTimeCtrl;
CString   endTime;
CEdit     descCtrl;
CString   desc;

  EditEntryDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~EditEntryDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_EditEntry };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void updateRcd();

public:
  afx_msg void OnOk();
  virtual BOOL OnInitDialog();
  afx_msg void onSelectEntry();
  afx_msg void OnChangeLogdate();
  afx_msg void OnChangeStarttime();
  afx_msg void OnChangeEnddate();
  afx_msg void OnChangeEndtime();
  afx_msg void OnLeaveLogdate();
  afx_msg void OnLeaveStarttime();
  afx_msg void OnLeaveEnddate();
  afx_msg void OnLeaveEndtime();
  afx_msg void OnLeaveLogactivity();
};
