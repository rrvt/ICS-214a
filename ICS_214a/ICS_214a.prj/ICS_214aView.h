// ICS_214aView.h : interface of the ICS_214aView class


#pragma once
#include "CScrView.h"
#include "ActvtyRpt.h"
#include "NotePadRpt.h"


class ICS_214aDoc;


class ICS_214aView : public CScrView {

ActvtyRpt dspActvty;
ActvtyRpt prtActvty;

protected:                                      // create from serialization only

  DECLARE_DYNCREATE(ICS_214aView)
  ICS_214aView() noexcept;

public:

  virtual ~ICS_214aView() { }

  virtual void displayHeader(DevBase& dev);
  virtual void displayFooter(DevBase& dev);

  virtual void onPreparePrinting(CPrintInfo* info);
  virtual void onBeginPrinting();
  virtual void onDisplayOutput();

  virtual void printHeader(DevBase& dev, int pageNo);
  virtual void printFooter(DevBase& dev, int pageNo);
  virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

          void initRptOrietn();
          void saveRptOrietn();

  ICS_214aDoc* GetDocument() const;

public:

  #ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
  #endif

  DECLARE_MESSAGE_MAP()

  afx_msg void onOptions();
  afx_msg void onRptOrietn();

  afx_msg void OnSetFocus(CWnd* pOldWnd);
  };


#ifndef _DEBUG  // debug version in ICS_214aView.cpp
inline ICS_214aDoc* ICS_214aView::GetDocument() const
   { return reinterpret_cast<ICS_214aDoc*>(m_pDocument); }
#endif

