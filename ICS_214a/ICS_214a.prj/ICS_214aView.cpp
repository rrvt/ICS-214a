// ICS_214aView.cpp : implementation of the ICS_214aView class


#include "stdafx.h"
#include "ICS_214aView.h"
#include "ICS_214aDoc.h"


// ICS_214aView

IMPLEMENT_DYNCREATE(ICS_214aView, CScrView)

BEGIN_MESSAGE_MAP(ICS_214aView, CScrView)
END_MESSAGE_MAP()



// ICS_214aView diagnostics

#ifdef _DEBUG

void ICS_214aView::AssertValid() const {CScrollView::AssertValid();}

void ICS_214aView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
ICS_214aDoc* ICS_214aView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ICS_214aDoc))); return (ICS_214aDoc*)m_pDocument;}

#endif //_DEBUG
