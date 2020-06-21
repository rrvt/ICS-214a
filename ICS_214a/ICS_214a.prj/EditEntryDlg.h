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
public:
  afx_msg void OnOk();
  virtual BOOL OnInitDialog();
  afx_msg void onSelectEntry();
};
