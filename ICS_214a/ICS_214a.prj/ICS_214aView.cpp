// ICS_214aView.cpp : implementation of the ICS_214aView class


#include "stdafx.h"
#include "ICS_214aView.h"
#include "ICS_214a.h"
#include "ICS_214aDoc.h"
#include "Options.h"
#include "Resources.h"


// ICS_214aView

IMPLEMENT_DYNCREATE(ICS_214aView, CScrView)

BEGIN_MESSAGE_MAP(ICS_214aView, CScrView)
END_MESSAGE_MAP()


ICS_214aView::ICS_214aView() noexcept : dspNote( nMgr.getNotePad()),  prtNote( pMgr.getNotePad()),
                                        dspActvty(dMgr.getNotePad()), prtActvty(pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


void ICS_214aView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) {
uint   x;
double topMgn   = options.topMargin.stod(x);
double leftMgn  = options.leftMargin.stod(x);
double rightMgn = options.rightMargin.stod(x);
double botMgn   = options.botMargin.stod(x);

  setIsNotePad(!notePad.isEmpty() || doc()->dataSrc() == NoteSource);

  setMgns(leftMgn,  topMgn,  rightMgn, botMgn, pDC);   CScrView::OnPrepareDC(pDC, pInfo);
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void ICS_214aView::onPrepareOutput(bool isNotePad, bool printing) {
DataSource ds = isNotePad ? NoteSource : doc()->dataSrc();

  switch (printing) {
    case true : switch(ds) {
                  case NoteSource   : prtNote.print(*this);   break;
                  case IncrActvtySrc:
                  case ActivitySrc  : prtActvty.print(*this); break;
                  case ExcelSrc     : prtActvty.print(*this); break;
                  }
                break;

    case false: switch(ds) {
                  case NoteSource :   dspNote.display(*this);   break;
                  case ActivitySrc:
                  case IncrActvtySrc:
                  case ExcelSrc:      dspActvty.display(*this); break;
                  }
                break;
    }

  CScrView::onPrepareOutput(isNotePad, printing);
  }


void ICS_214aView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo) {

  switch(doc()->dataSrc()) {
    case NoteSource   : setOrientation(options.orient); break;    // Setup separate Orientation?
    case IncrActvtySrc:
    case ExcelSrc     :
    case ActivitySrc  : setOrientation(options.orient); break;
    }

  setPrntrOrient(theApp.getDevMode(), pDC);   CScrView::OnBeginPrinting(pDC, pInfo);
  }



// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void ICS_214aView::printFooter(Device& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NoteSource   : prtNote.footer(dev, pageNo);   break;
    case IncrActvtySrc:
    case ExcelSrc     :
    case ActivitySrc  : prtActvty.footer(dev, pageNo); break;
    }
  }


void ICS_214aView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NoteSource : break;
    case ActivitySrc: break;
    }
  }


// ICS_214aView diagnostics

#ifdef _DEBUG

void ICS_214aView::AssertValid() const {CScrollView::AssertValid();}

void ICS_214aView::Dump(CDumpContext& dc) const {CScrollView::Dump(dc);}
                                             // non-debug version is inline
ICS_214aDoc* ICS_214aView::GetDocument() const
  {ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(ICS_214aDoc))); return (ICS_214aDoc*)m_pDocument;}

#endif //_DEBUG
