// ICS_214aDoc.h : interface of the ICS_214aDoc class


#pragma once
#include "CDoc.h"


enum DataSource {NotePadSrc, ActivitySrc, IncrActvtySrc, ExcelSrc, ExcelSrc2};


class ICS_214aDoc : public CDoc {

DataSource dataSource;

#if 1
PathDlgDsc pathDlgDsc;
#else
String     defFileName;                                             // _T("mumble.txt")
String     defExt;                                                  // _T("txt")
String     defFilePat;                                              // _T("*.txt")
#endif

protected: // create from serialization only

  ICS_214aDoc() noexcept;
  DECLARE_DYNCREATE(ICS_214aDoc)

public:

  virtual ~ICS_214aDoc() { }

  DataSource dataSrc() {return dataSource;}
  void       display(DataSource ds);

  virtual void serialize(Archive& ar);

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

private:

  void saveDoc(String& path);

protected:

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void OnNewLog();
  afx_msg void OnFileOpen();
  afx_msg void onSave214();
  afx_msg void onSaveExcel();
  afx_msg void onSaveExcel2();
  afx_msg void OnEditHeader();
  afx_msg void OnLogEntry();
  afx_msg void OnStopEntry();
  afx_msg void OnEditLogEntry();
  afx_msg void OnCalibDspPrt();
  };





//  String& getDefFileName();

