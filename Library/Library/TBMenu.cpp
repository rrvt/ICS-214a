// ToolBar Drop Down Menu


#include "pch.h"
#include "TBMenu.h"


TBMenu* TBMenu::install(uint idr, TCchar* caption) {
CMenu menu;  if (!menu.LoadMenu(idr)) return 0;
int   n;                                                      // rrvt test
int   i;
int   id;

  for (i = 0, n = menu.GetMenuItemCount(); i < n; i++) {
    id = menu.GetMenuItemID(i);   menu.EnableMenuItem(id, MF_ENABLED);
    }

  Initialize(m_nID, menu.GetSafeHmenu(), -1, caption);   m_bText = true;   m_bImage = false;

  return this;
  }


TBMenu* TBMenu::install(uint idr, uint imageIndex) {
CMenu menu;  if (!menu.LoadMenu(idr)) return 0;

  Initialize(m_nID, menu.GetSafeHmenu(), -1);   SetImage(imageIndex);   return this;
  }



TBMenu* TBMenu::install(const CbxItem cbxItem[], int n, TCchar* caption) {
  return 0;
  }


TBMenu* TBMenu::install(const CbxItem cbxItem[], int n, uint imageIndex) {
  return 0;
  }


#if 0
void TBMenu::addItem(TCchar* txt, int data) {

  setMaxChars(txt);

  if (FindItem(txt) < 0) AddItem(txt, data);
  }


TBMenu* TBMenu::finInstall(TCchar* caption) {

  m_dwStyle = CBS_DROPDOWN | WS_VSCROLL | BS_FLAT | BS_VCENTER | BS_NOTIFY;

  this->caption = caption;   setMaxChars(caption);

  m_iWidth = toolBarDim.getHoriz(maxChars) + 20;   return this;
  }
#endif
