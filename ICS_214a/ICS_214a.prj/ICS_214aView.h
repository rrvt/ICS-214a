// ICS_214aView.h : interface of the ICS_214aView class


#pragma once
#include "CScrView.h"


class ICS_214aDoc;


class ICS_214aView : public CScrView {

protected:                                      // create from serialization only

  ICS_214aView() noexcept { }
  DECLARE_DYNCREATE(ICS_214aView)

public:

  virtual ~ICS_214aView() { }

  virtual void onPrepareOutput();
  virtual void printFooter(Display& dev, int pageNo);

  ICS_214aDoc* GetDocument() const;

public:

  #ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
  #endif

  DECLARE_MESSAGE_MAP()
  virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
};


#ifndef _DEBUG  // debug version in ICS_214aView.cpp
inline ICS_214aDoc* ICS_214aView::GetDocument() const
   { return reinterpret_cast<ICS_214aDoc*>(m_pDocument); }
#endif

