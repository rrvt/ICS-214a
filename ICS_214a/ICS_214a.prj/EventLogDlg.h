#pragma once


// EventLogDlg dialog

class EventLogDlg : public CDialogEx
{
  DECLARE_DYNAMIC(EventLogDlg)

public:
CEdit   logDateCtrl;
CString logDate;
CEdit   startTimeCtrl;
CString startTime;
CEdit   endTimeCtrl;
CString endTime;
CString logActivity;

  EventLogDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~EventLogDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_EventLogEntry };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnChangeLogdate();
  afx_msg void OnChangeStarttime();
  afx_msg void OnChangeEndtime();
  };
