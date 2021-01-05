// ICS_214aView.h : interface of the ICS_214aView class


#pragma once
#include "CScrView.h"
#include "ActvtyRpt.h"
#include "NoteRptB.h"


class ICS_214aDoc;


class ICS_214aView : public CScrView {

NoteRptB  dspNote;
NoteRptB  prtNote;
ActvtyRpt dspActvty;
ActvtyRpt prtActvty;

protected:                                      // create from serialization only

  ICS_214aView() noexcept;
  DECLARE_DYNCREATE(ICS_214aView)

public:

  virtual ~ICS_214aView() { }

  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
  virtual void onPrepareOutput(bool isNotePad, bool printing);

  virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
  virtual void printFooter(Device& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

  ICS_214aDoc* GetDocument() const;

public:

  #ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
  #endif

  DECLARE_MESSAGE_MAP()

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in ICS_214aView.cpp
inline ICS_214aDoc* ICS_214aView::GetDocument() const
   { return reinterpret_cast<ICS_214aDoc*>(m_pDocument); }
#endif

