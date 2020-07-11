// ICS_214aView.cpp : implementation of the ICS_214aView class


#include "stdafx.h"
#include "ICS_214aView.h"
#include "ICS_214aDoc.h"
#include "Options.h"
#include "Report.h"


// ICS_214aView

IMPLEMENT_DYNCREATE(ICS_214aView, CScrView)

BEGIN_MESSAGE_MAP(ICS_214aView, CScrView)
END_MESSAGE_MAP()


void ICS_214aView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  if (pDC->IsPrinting()) {setHorzMgns(leftMgn, rightMgn); setVertMgns(topMgn, botMgn);}
  else                   {setHorzMgns(0.33, 0.33); setVertMgns(0.33, 0.33);}

  CScrView::OnPrepareDC(pDC, pInfo);
  }


void ICS_214aView::onPrepareOutput() {report(isPrinting());   CScrView::onPrepareOutput();}


void ICS_214aView::printFooter(Display& dev, int pageNo) {report.footer(dev, pageNo); invalidate();}


// ICS_214aView diagnostics

#ifdef _DEBUG

void ICS_214aView::AssertValid() const {CScrollView::AssertValid();}

void ICS_214aView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
ICS_214aDoc* ICS_214aView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ICS_214aDoc))); return (ICS_214aDoc*)m_pDocument;}

#endif //_DEBUG
