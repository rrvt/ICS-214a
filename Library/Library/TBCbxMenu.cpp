// Drop Down Menu constructed in a Combo Box

\
#include "pch.h"
#include "TBCbxMenu.h"
#include "CbxItem.h"
#include "ToolBarDim.h"

#include "MessageBox.h"


TBCbxMenu& TBCbxMenu::install(int idr, TCchar* caption) {
CMenu      menu;
uint       i;
uint       n;
Cstring    txt;

  if (!menu.LoadMenu(idr)) return *(TBCbxMenu*)0;

    for (i = 0, maxChars = 0, n = menu.GetMenuItemCount(); i < n; i++)
                       {menu.GetMenuString(i, txt, MF_BYPOSITION);   addItem(txt, menu.GetMenuItemID(i));}

  menu.DestroyMenu();   return finInstall(caption);
  }


TBCbxMenu& TBCbxMenu::install(const CbxItem cbxItem[], int n, TCchar* caption) {
int     i;

  for (i = 0, maxChars = 0; i < n; i++)
                                       {const CbxItem& item = cbxItem[i];   addItem(item.txt, item.data);}

  return finInstall(caption);
  }


void TBCbxMenu::addItem(TCchar* txt, int data) {

  setMaxChars(txt);

  if (FindItem(txt) < 0) AddItem(txt, data);
  }


TBCbxMenu& TBCbxMenu::finInstall(TCchar* caption) {

  this->caption = caption;   setMaxChars(caption);

  m_iWidth = toolBarDim.getHoriz(maxChars) + 20;

  m_dwStyle = CBS_DROPDOWNLIST | WS_VSCROLL | BS_VCENTER;   SetFlatMode(true);

  return *this;
  }


bool TBCbxMenu::setCaption() {

  if (!getActual()) return false;

#if 1
  actual->SetText(caption);   return true;
#else
CMFCToolBarComboBoxButton* cbxBtn = GetByCmd(id);   if (!cbxBtn) return false;
CEdit*                     edit   = cbxBtn->GetEditCtrl();

  edit->SetReadOnly();   edit->ModifyStyle(0, ES_CENTER);   edit->SetWindowText(caption);   return true;
#endif
  }


uint TBCbxMenu::getCmdId() {
CMFCToolBarComboBoxButton* cbxBtn = GetByCmd(id);   if (!cbxBtn) return 0;
int i = cbxBtn->GetCurSel();

  return i >= 0 ? cbxBtn->GetItemData(i) : 0;
  }




bool TBCbxMenu::getActual() {if (!actual) actual = GetByCmd(id);   return actual != 0;}



#if 0
bool TBCbxMenu::setCaption(uint id, TCchar* txt, TBBtnCtx& ctx) {
TBCbxMenu* cbx = TBCbxMenu::get(id);   if (!cbx) return false;

  ctx.setMaxChars(txt);

  cbx->setCaption(txt);   cbx->setDim(ctx);   return true;
  }
#endif
#if 1
#else
    m_dwStyle = CBS_DROPDOWN | WS_VSCROLL | BS_FLAT | BS_VCENTER | BS_NOTIFY;

    this->caption = caption;   t = _tcslen(caption);    if (t > maxChars) maxChars = t;

    m_iWidth = toolBarDim.getHoriz(maxChars) + 20;

  menu.DestroyMenu();  return *this;
#endif
#if 1
#else
  int t;
  t = _tcslen(txt);   if (t > maxChars) maxChars = t;
#endif
#if 1
#else
  int t;
  t = _tcslen(caption);    if (t > maxChars) maxChars = t;
#endif
#if 1
#else
      uint       itemId;
      int        t;
      itemId = menu.GetMenuItemID(i);   menu.GetMenuString(i, name, MF_BYPOSITION);

      t = name.length();   if (t > maxChars) maxChars = t;

      if (find(name) < 0) AddItem(name, itemId);
#endif
#if 1
#else
    int     t;
    String& txt = cbxItem[i].txt;

    t = txt.length();   if (t > maxChars) maxChars = t;

    if (find(txt) < 0) AddItem(txt, cbxItem[i].data);
#endif

