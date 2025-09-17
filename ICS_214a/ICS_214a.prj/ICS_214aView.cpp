// ICS_214aView.cpp : implementation of the ICS_214aView class


#include "stdafx.h"
#include "ICS_214aView.h"
#include "ICS_214a.h"
#include "ICS_214aDoc.h"
#include "IniFileEx.h"
#include "OptionsDlg.h"
#include "Resource.h"
#include "ResourceData.h"
#include "RptOrientDlgTwo.h"


static TCchar* ActyOrietnKey = _T("Activity");


// ICS_214aView

IMPLEMENT_DYNCREATE(ICS_214aView, CScrView)

BEGIN_MESSAGE_MAP(ICS_214aView, CScrView)
  ON_COMMAND(ID_Options,     &onOptions)
  ON_COMMAND(ID_Orientation, &onRptOrietn)
  END_MESSAGE_MAP()


ICS_214aView::ICS_214aView() noexcept : dspActvty(dMgr.getNotePad()), prtActvty(pMgr.getNotePad()) {
ResourceData res;
String       pn;
  if (res.getProductName(pn)) prtNote.setTitle(pn);
  }


void ICS_214aView::onOptions() {
OptionsDlg dlg;

  if (printer.name.isEmpty()) printer.load(0);

  initNoteOrietn();

  if (dlg.DoModal() == IDOK) {pMgr.setFontScale(printer.scale);   saveNoteOrietn();}
  }




void ICS_214aView::initRptOrietn() {
  dspActvty.prtrOrietn  = prtActvty.prtrOrietn  =
                                  (PrtrOrient) iniFile.readInt(RptOrietnSect, ActyOrietnKey,  PortOrient);
  }


void ICS_214aView::onRptOrietn() {
RptOrietnDlg dlg;

  dlg.lbl01 = _T("Activity:");
  dlg.ntpd  = printer.toStg(prtNote.prtrOrietn);
  dlg.rpt1  = printer.toStg(prtActvty.prtrOrietn);

  if (dlg.DoModal() == IDOK) {
    dspNote.prtrOrietn    = prtNote.prtrOrietn    = printer.toOrient(dlg.ntpd);
    dspActvty.prtrOrietn  = prtActvty.prtrOrietn  = printer.toOrient(dlg.rpt1);
    saveNoteOrietn();   saveRptOrietn();
    }
  }


void ICS_214aView::saveRptOrietn()
                               {iniFile.write(RptOrietnSect, ActyOrietnKey,  (int) prtActvty.prtrOrietn);}


void ICS_214aView::onPreparePrinting(CPrintInfo* info) {
  switch(doc()->dataSrc()) {
    case NotePadSrc  : prtNote.onPreparePrinting(info);   break;
    case ActivitySrc : prtActvty.onPreparePrinting(info); break;
    case ExcelSrc    : prtActvty.onPreparePrinting(info); break;
    }
  }


// Perpare output (i.e. report) then start the output with the call to SCrView

void ICS_214aView::onBeginPrinting() {

  switch(doc()->dataSrc()) {
    case NotePadSrc   : prtNote.onBeginPrinting(*this);   break;
    case IncrActvtySrc:
    case ActivitySrc  : prtActvty.onBeginPrinting(*this); break;
    case ExcelSrc     : prtActvty.onBeginPrinting(*this); break;
    }
  }


void ICS_214aView::onDisplayOutput() {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.display(*this);   break;
    case ActivitySrc  :
    case IncrActvtySrc:
    case ExcelSrc     : dspActvty.display(*this); break;
    }
  }


void ICS_214aView::displayHeader(DevStream& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspHeader(dev);   break;
    case ActivitySrc  :
    case IncrActvtySrc:
    case ExcelSrc     : dspActvty.dspHeader(dev); break;
    }
  }


void ICS_214aView::displayFooter(DevStream& dev) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : dspNote.dspFooter(dev);   break;
    case ActivitySrc  :
    case IncrActvtySrc:
    case ExcelSrc     : dspActvty.dspFooter(dev); break;
    }
  }


void ICS_214aView::printHeader(DevStream& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : prtNote.prtHeader(dev, pageNo);   break;
    case IncrActvtySrc:
    case ExcelSrc     :
    case ActivitySrc  : prtActvty.prtHeader(dev, pageNo); break;
    }
  }


// The footer is injected into the printed output, so the output goes directly to the device.
// The output streaming functions are very similar to NotePad's streaming functions so it should not
// be a great hardship to construct a footer.

void ICS_214aView::printFooter(DevStream& dev, int pageNo) {
  switch(doc()->dataSrc()) {
    case NotePadSrc   : prtNote.prtFooter(dev, pageNo);   break;
    case IncrActvtySrc:
    case ExcelSrc     :
    case ActivitySrc  : prtActvty.prtFooter(dev, pageNo); break;
    }
  }


void ICS_214aView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo) {

  CScrView::OnEndPrinting(pDC, pInfo);

  switch(doc()->dataSrc()) {
    case NotePadSrc : break;
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
