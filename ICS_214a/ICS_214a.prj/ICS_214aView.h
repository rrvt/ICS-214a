// ICS_214aView.h : interface of the ICS_214aView class


#pragma once
#include "CScrView.h"


class ICS_214aDoc;


class ICS_214aView : public CScrView {

protected: // create from serialization only

  ICS_214aView() noexcept { }
  DECLARE_DYNCREATE(ICS_214aView)

public:

  virtual ~ICS_214aView() { }

  ICS_214aDoc* GetDocument() const;

public:

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

protected:

//  DECLARE_MESSAGE_MAP()
public:
  DECLARE_MESSAGE_MAP()
  };


#ifndef _DEBUG  // debug version in ICS_214aView.cpp
inline ICS_214aDoc* ICS_214aView::GetDocument() const
   { return reinterpret_cast<ICS_214aDoc*>(m_pDocument); }
#endif

