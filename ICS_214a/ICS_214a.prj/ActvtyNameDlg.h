// ICS-214a header and footer information



#pragma once
#include "Resource.h"


// ActvtyNameDlg dialog

class ActvtyNameDlg : public CDialogEx {

  DECLARE_DYNAMIC(ActvtyNameDlg)

bool updateTime;
bool updateDate;

public:

CString name;
CEdit   prepDateCtrl;
CString prepDate;
CEdit   prepTimeCtrl;
CString prepTime;
CString leaderName;
CString leaderPosition;
CString opPeriod;
CString prepBy;
CString missionNo;

  ActvtyNameDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~ActvtyNameDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_ActvtyName };
#endif

private:

bool vrfyMnth( int cnt, TCchar ch, int& v);
bool vrfyDay(  int cnt, TCchar ch, int& v);
bool vrfyYr(   int cnt, TCchar ch, int& v);
void replDtSel(int i,   TCchar ch);

bool vrfyHr(   int cnt, TCchar ch, int& v);
bool vrfyMin(  int cnt, TCchar ch, int& v);
void replTmSel(int i,   TCchar ch);

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnChangePrepdate();
  afx_msg void OnChangePreptime();
};
