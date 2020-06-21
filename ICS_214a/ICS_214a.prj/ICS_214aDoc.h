// ICS_214aDoc.h : interface of the ICS_214aDoc class


#pragma once
#include "CDoc.h"


class ICS_214aDoc : public CDoc {

String saveAsTitle;                                             // Save As Parameters, examples:
String defFileName;                                             // _T("mumble.txt")
String defExt;                                                  // _T("txt")
String defFilePat;                                              // _T("*.txt")

protected: // create from serialization only

  ICS_214aDoc() noexcept;
  DECLARE_DYNCREATE(ICS_214aDoc)

public:

  virtual ~ICS_214aDoc() { }

  virtual void serialize(Archive& ar);

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnNewLog();
  afx_msg void OnFileOpen();
  afx_msg void OnFileSave();
  afx_msg void OnEditHeader();
  afx_msg void OnLogEntry();
  afx_msg void OnStopEntry();
  afx_msg void OnEditLogEntry();
  };
