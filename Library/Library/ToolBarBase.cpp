// Tool Bar to be used with Button and ComboBox


#include "pch.h"
#include "ToolBarBase.h"
#include "TBButton.h"
#include "TBCbxMenu.h"                    // Use for Menus on Dialog Box Tool Bars
#include "TBMenu.h"                       // Use for Menus in Doc/View applications
#include "WinPos.h"
#ifdef DsplyHistory
#include "History.h"                      // Debug Only
#endif


static const DWORD TBStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_FLYBY |
AFX_DEFAULT_TOOLBAR_STYLE;


bool ToolBarBase::create(CWnd* wnd, uint id, DWORD style) {
CRect rect;

  if (!CreateEx(wnd, TBSTYLE_FLAT, TBStyle | style)) return false;

  if (!LoadToolBar(id, 0, 0, TRUE)) return false;

  wnd->RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, AFX_IDW_TOOLBAR);

  window = wnd;   return true;
  }


void ToolBarBase::move(CRect& winRect) {
CRect rect;
int   hDelta = winPos.dluToScreen(7);
int   vDelta = winPos.dluToScreen(10, false);

  GetWindowRect(&rect);

  rect.bottom = rect.top  + vDelta;
  rect.left   += hDelta;
  rect.right  = rect.left + winRect.right - winRect.left - 2*hDelta;

  ScreenToClient(rect);   MoveWindow(&rect);
  }


void ToolBarBase::OnFillBackground(CDC* pDC)
                      {CRect rect;   GetClientRect(&rect);   pDC->FillSolidRect(&rect, RGB(255,255,255));}







#if 0
bool ToolBarBase::installBtn(uint id, TCchar* caption) {
TBButton  btn(id);
TBBtnCtx& ctx = addCtx(id);   ctx.initialize(toolBarDim.width, toolBarDim.height);   getFontDim(ctx);

  btn.install(caption);   return ReplaceButton(id, btn) > 0;
  }


bool ToolBarBase::installComboBox(uint id) {
TBComboBox btn(id);
TBBtnCtx&  ctx = addCtx(id);   ctx.initialize(toolBarDim.width, toolBarDim.height);   getFontDim(ctx);

  btn.install(ctx);

  return ReplaceButton(id, btn) > 0;
  }


bool ToolBarBase::installEditBox(uint id, int noChars) {
TBEditBox btn(id);
TBBtnCtx& ctx = addCtx(id);   ctx.initialize(toolBarDim.width, toolBarDim.height);   getFontDim(ctx);

  ctx.maxChars = noChars;

  btn.install(ctx);   return ReplaceButton(id, btn) > 0;
  }


bool ToolBarBase::installPopupMenu(uint id, bool flatMode) {
TBComboBox btn(id);
TBBtnCtx&  ctx = addCtx(id);   ctx.initialize(toolBarDim.width, toolBarDim.height);   getFontDim(ctx);

  btn.install(ctx, flatMode);

  return ReplaceButton(id, btn) > 0;
  }


bool ToolBarBase::addPopupItems(uint id, const CbxItem* items, int noItems, bool sorted) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx) return false;

  if (TBComboBox::addItems(id, items, noItems, ctx, sorted)) adjust(ctx);

  return true;
  }


bool ToolBarBase::addPopupItem(uint id, CbxItem& item, bool sorted) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx) return false;

  if (TBComboBox::addItem(id, item, ctx, sorted)) adjust(ctx);

  return true;
  }


// Add a Resource Menu to popup

void ToolBarBase::addPopupMenu(uint id, uint idr, bool sorted) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx) return;

  if (TBComboBox::addRes(id, idr, ctx, sorted)) adjust(ctx);
  }


void ToolBarBase::setPopupCaption(uint id, TCchar* caption) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx) return;

  TBComboBox::setCaption(id, caption, ctx);   adjust(ctx);    TBComboBox::setCaption(id, caption, ctx);
  }


void ToolBarBase::setButtonTxt(uint id, TCchar* caption) {
int index = CommandToIndex(id);

  SetButtonText(index, caption);
  }


bool ToolBarBase::installMenu(uint id, uint idr, TCchar* caption) {
TBMenu btn(id);

  btn.install(idr, caption);   return ReplaceButton(id, btn) > 0;
  }


bool ToolBarBase::installMenu(uint id, uint idr, uint imageIndex) {
TBMenu btn(id);

  btn.install(idr, imageIndex);   return ReplaceButton(id, btn) > 0;
  }


void ToolBarBase::addCbxItems(uint id, CbxItem* items, int nItems, bool sorted) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx || !nItems) return;

  if (TBComboBox::addItems(id, items, nItems, ctx, sorted)) adjust(ctx);
  }


// Add a single item to combo box

void ToolBarBase::addCbxItem (uint id, CbxItem& item, bool sorted) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx) return;

  if (TBComboBox::addItem(id, item, ctx, sorted)) adjust(ctx);
  }


// Add Caption to combo box, should be last...

void ToolBarBase::setCbxCaption(uint id, TCchar* caption) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx) return;

  if (TBComboBox::setCaption(id, caption, ctx)) adjust(ctx);

  TBComboBox::setCaption(id, caption, ctx);
  }


void ToolBarBase::addResToCbx(uint id, uint idr, bool sorted) {
TBBtnCtx& ctx = *findCtx(id);   if (!&ctx) return;

  if (TBComboBox::addRes(id, idr, ctx, sorted)) adjust(ctx);
  }


bool ToolBarBase::setEbxText(uint id, TCchar* txt) {
TBEditBox* ebx = TBEditBox::get(id);   if (!ebx) return false;

  ebx->setText(txt);   return true;
  }


bool ToolBarBase::getEbxText(uint id, String& txt) {
TBEditBox* ebx = TBEditBox::get(id);   if (!ebx) return false;

  ebx->getText(txt);   return true;
  }


TBMenu* ToolBarBase::getMenuBtn(uint id) {
int  n = GetCount();
int  i;

  for (i = 0; i < n; i++) if (GetItemID(i) == id) return (TBMenu*) GetButton(i);

  return 0;
  }


// Adjust the tool bar after changing dim of a button

void ToolBarBase::adjust(TBBtnCtx& ctx) {if (ctx.dirty) {AdjustLayout();   ctx.dirty = false;}}



void ToolBarBase::getFontDim(TBBtnCtx& ctx) {     //
CDC*       dc;
CWnd*      wnd;
TEXTMETRIC metric;

  if (!toolBarDim.fontDim.width) {

    for (dc = GetDC(), wnd = 0; !dc; dc = wnd->GetDC()) {
      wnd = wnd ? wnd->GetParent() : GetParent();   if (!wnd) break;
      }

    if (!dc) {toolBarDim.fontDim.width = 12; toolBarDim.fontDim.height = 21; return;}

    dc->GetTextMetrics(&metric);

    toolBarDim.fontDim.width = (3 * metric.tmAveCharWidth + metric.tmMaxCharWidth) / 4;

    toolBarDim.fontDim.height = metric.tmHeight * 1333 / 1000;
    }

  ctx.avgWidth = toolBarDim.fontDim.width;   ctx.height    = toolBarDim.fontDim.height;
  ctx.winWidth = toolBarDim.width;   ctx.winHeight = toolBarDim.height;
  }
#endif


void ToolBarBase::getFontDim(FontDim& fontDim) {
CDC*       dc;
CWnd*      wnd;
TEXTMETRIC metric;

  for (dc = GetDC(), wnd = 0; !dc; dc = wnd->GetDC()) {
    wnd = wnd ? wnd->GetParent() : GetParent();   if (!wnd) break;
    }

  if (!dc) {toolBarDim.fontDim.width = 12; toolBarDim.fontDim.height = 21; return;}

  dc->GetTextMetrics(&metric);

  fontDim.width = (3 * metric.tmAveCharWidth + metric.tmMaxCharWidth) / 4;

  fontDim.height = metric.tmHeight * 1333 / 1000;
  }


bool ToolBarBase::add(TBButton&  button, uint id, TCchar* caption) {
  button.install(caption);   return ReplaceButton(id, button) > 0;
  }


bool ToolBarBase::add(TBEditBox& button, uint id, int noChars) {
  button.install(noChars);   return ReplaceButton(id, button) > 0;
  }


bool ToolBarBase::add(TBMenu&  button, uint id, int idr, TCchar* caption) {
  bool rslt = ReplaceButton(id, *button.install(idr, caption)) > 0;   return rslt;
  }


bool ToolBarBase::add(TBMenu&  button, uint id, int idr, int index) {
  bool rslt = ReplaceButton(id, *button.install(idr, index)) > 0;   return rslt;
  }



bool ToolBarBase::add(TBMenu&  button, uint id, const CbxItem cbxItem[], int n, TCchar* caption) {
  bool rslt = ReplaceButton(id, *button.install(cbxItem, n, caption)) > 0;   return rslt;
  }


bool ToolBarBase::add(TBCbxMenu& button, uint id, int idr, TCchar* caption) {
bool rslt = ReplaceButton(id, button.install(idr, caption)) > 0;

  button.setCaption();   return rslt;
  }


bool ToolBarBase::add(TBCbxMenu& button, uint id, const CbxItem cbxItem[], int n, TCchar* caption) {
bool rslt = ReplaceButton(id, button.install(cbxItem, n, caption)) > 0;

  if (rslt) button.setCaption();   return rslt;
  }


bool ToolBarBase::add(TBCboBx& button, uint id, int noChars) {
  return ReplaceButton(id, *button.install(noChars)) > 0;
  }


bool ToolBarBase::add(TBCboBx& button, uint id, int idr, TCchar* caption) {
bool rslt = ReplaceButton(id, *button.install(idr, caption)) > 0;

  if (rslt) button.setCaption();   return rslt;
  }


bool ToolBarBase::add(TBCboBx& button, uint id, const CbxItem cbxItem[], int n, TCchar* caption) {
bool rslt = ReplaceButton(id, *button.install(cbxItem, n, caption)) > 0;

  if (rslt) button.setCaption();   return rslt;
  }




void ToolBarBase::dispatch(TBCbxMenu& cbxMenu) {
uint cmdID = cbxMenu.getCmdId();

  if (cmdID) PostMessage(WM_COMMAND, cmdID, 0);

  cbxMenu.setCaption();
  }




// Button Flying Tips are implemented here for applications without a Framework (i.e. MainFrame)
// Add the following to message map
//   ON_NOTIFY_EX( TTN_NEEDTEXT, 0,   &OnTtnNeedText)
// and add the following afx_msg to the application somewhere (e.g. a dialog box)
// BOOL MyApp::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
//                                                                {return toolBar.OnTtnNeedText(pNMHDR);}

bool ToolBarBase::OnTtnNeedText(NMHDR* pNMHDR) {
NMTTDISPINFO* pTTT = (NMTTDISPINFO*) pNMHDR;
ButtonBase*   btn;                           // Base class of all buttons
Cstring       s;                             // CString in which resource string with button ID is stored

#ifdef DsplyHistory
HistData&     h = history.nextData();   h.flags = pTTT->uFlags;
#endif

  if (pTTT->uFlags & TTF_CENTERTIP) return false;     // Do not process center tooltip requiests

  if ((pTTT->uFlags & 0x040) == 0) return false;      // Tooltips appear to have this bit define as one
                                                      // for mouse pointer tooltips
  if (!getMouseHover(btn)) return false;

  s.loadRes(btn->m_nID);   if (s.isEmpty()) return false;

#ifdef DsplyHistory
h.id = btn->m_nID;
#endif

  _stprintf_s(pTTT->szText, noElements(pTTT->szText), _T("%s"), s.str());   return true;
  }


bool ToolBarBase::getMouseHover(ButtonBase*& btn) {
CPoint point;                                         // point relative to toolbar client area
int    n;                                             // number of buttons
int    i;
CRect  rect;                                          // button rectangle relative to toolbar client area
                                                      // for mouse pointer tooltips
  GetCursorPos(&point);   ScreenToClient(&point);     // point relative to toolbar cliend area

  for (i = 0, n = GetCount(), btn = 0; i < n; i++) {
    GetItemRect(i, &rect);

    if (rect.left <= point.x && point.x < rect.right) {btn = GetButton(i);   return btn != 0;}
    }

  return false;
  }



#if 0
TBBtnCtx& ToolBarBase::addCtx(uint id) {
TBBtnCtx* ctx = findCtx(id);

  if (ctx) return *ctx;

  ctx = data.allocate();   data = ctx;   ctx->id = id;  return *ctx;
  }


TBBtnCtx* ToolBarBase::findCtx(uint id) {
TlBrIter  iter(*this);
TBBtnCtx* ctx;

  for (ctx = iter(); ctx; ctx = iter++) if (ctx-> id == id) return ctx;

  return 0;
  }


// ToolBarBase Button Flying Tips are implemented hereit for applications without a Framework (i.e. MainFrame)
// Add the following to message map
//   ON_NOTIFY_EX( TTN_NEEDTEXT, 0,   &OnTtnNeedText)
// and add the following afx_msg to the application somewhere (e.g. a dialog box)
// BOOL MyApp::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
//                                                                {return toolBar.OnTtnNeedText(pNMHDR);}

bool ToolBarBase::OnTtnNeedText(NMHDR* pNMHDR) {
NMTTDISPINFO* pTTT = (NMTTDISPINFO*) pNMHDR;
ButtonBase*   btn;                           // Base class of all buttons
Cstring       s;                             // CString in which resource string with button ID is stored

#ifdef DsplyHistory
HistData&     h = history.nextData();   h.flags = pTTT->uFlags;
#endif

  if (pTTT->uFlags & TTF_CENTERTIP) return false;     // Do not process center tooltip requiests

  if ((pTTT->uFlags & 0x040) == 0) return false;      // Tooltips appear to have this bit define as one
                                                      // for mouse pointer tooltips
  if (!getMouseHover(btn)) return false;

  s.loadRes(btn->m_nID);   if (s.isEmpty()) return false;

#ifdef DsplyHistory
h.id = btn->m_nID;
#endif

  _stprintf_s(pTTT->szText, noElements(pTTT->szText), _T("%s"), s.str());   return true;
  }


bool ToolBarBase::getMouseHover(ButtonBase*& btn) {
CPoint point;                                         // point relative to toolbar client area
int    n;                                             // number of buttons
int    i;
CRect  rect;                                          // button rectangle relative to toolbar client area
                                                      // for mouse pointer tooltips
  GetCursorPos(&point);   ScreenToClient(&point);     // point relative to toolbar cliend area

  for (i = 0, n = GetCount(), btn = 0; i < n; i++) {
    GetItemRect(i, &rect);

    if (rect.left <= point.x && point.x < rect.right) {btn = GetButton(i);   return btn != 0;}
    }

  return false;
  }
#endif


#if 0
void ToolBarBase::setWinAttributes(CRect& winRect)
    {toolBarDim.height = winRect.bottom - winRect.top;   toolBarDim.width = winRect.right - winRect.left;}
#endif

