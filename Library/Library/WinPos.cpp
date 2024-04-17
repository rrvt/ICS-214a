// Manage Window Position and Size


#include "pch.h"
#include "WinPos.h"
#include "IniFile.h"

#include "MessageBox.h"

WinPos winPos;


WinPos::WinPos() : hDLUtoPxls(1), vDLUtoPxls(1), defWidth(100), defDepth(100) {
RECT rsys;

  SystemParametersInfo(SPI_GETWORKAREA, 0, &rsys, 0);

  screenWidth = rsys.right;   screenHeight = rsys.bottom;
  }


void WinPos::setDLUToPxls(RECT& rect, int hDLU, int vDLU) {
double dlu;

  dlu = hDLU;  hDLUtoPxls = (rect.right - rect.left) / dlu;
  dlu = vDLU;  vDLUtoPxls = (rect.bottom - rect.top) / dlu;
  }


int WinPos::dluToScreen(int dlu, bool horiz) {
double t = dlu;   return int(t * (horiz ? hDLUtoPxls : vDLUtoPxls) + 0.5);
}


void WinPos::initialPos(CWnd* wnd, RECT& defaultRect) {

  data.load(defaultRect);   data.normalize(screenWidth, screenHeight);

  wnd->SetWindowPos(0, data.left, data.top, data.width, data.depth, SWP_NOCOPYBITS);   // | SWP_NOACTIVATE
  }


static TCchar* WindowPosData = _T("Window Position Data");
static TCchar* Left          = _T("Left");
static TCchar* Top           = _T("Top");
static TCchar* Width         = _T("Width");
static TCchar* Depth         = _T("Depth");


void WinPosData::save() {
  iniFile.write(WindowPosData, Left,  left);
  iniFile.write(WindowPosData, Top,   top);
  iniFile.write(WindowPosData, Width, width);
  iniFile.write(WindowPosData, Depth, depth);
  }


void WinPosData::load(RECT& defaultRect) {
  left   = iniFile.readInt(WindowPosData, Left,  defaultRect.left);
  top    = iniFile.readInt(WindowPosData, Top,   defaultRect.top);
  width  = iniFile.readInt(WindowPosData, Width, defaultRect.right  - defaultRect.left);
  depth  = iniFile.readInt(WindowPosData, Depth, defaultRect.bottom - defaultRect.top);

  defWidth = width;              defDepth = depth;
  minWidth = int(width / 4.0);   minDepth = int(depth / 4.0);

  rationalize();
  }



WinPosData& WinPosData::operator= (RECT& r) {
int w = r.right - r.left;
int d = r.bottom - r.top;

  left = r.left; top = r.top;

  if      (w >  width)   {width = w; minWidth = int (width / 3.0);}
  else if (w >= minWidth) width = w;
  else                    width = minWidth;

  if      (d > depth)    {depth = d; minDepth = int(depth / 3.0);}
  else if (d >= minDepth) depth = d;
  else                    depth = minDepth;

  return *this;
  }


void WinPosData::set(int& cx, int& cy) {

  if      (cx >  defWidth) {width = defWidth = cx;   minWidth = int (width / 3.0);}
  else if (cx >= minWidth)  width = cx;
  else                     {display(_T("<: "), cx); width = cx = minWidth;}

  if      (cy >  defDepth) {depth = defDepth = cy;   minDepth = int(depth / 3.0);}
  else if (cy >= minDepth)  depth = cy;
  else                      depth = cy = minDepth;
  }


void WinPosData::display(TCchar* tgt, int d) {
String s;

  s.format(_T("%s: %i, %i, %i, %i"), tgt, d, width, defWidth, minWidth);
  messageBox(s);
  }


void WinPosData::normalize(int screenWidth, int screenHeight) {

  rationalize();
  if (screenWidth  < width)        width = minWidth;
  if (screenHeight < depth)        depth = minDepth;
  if (left + width > screenWidth)  left  = screenWidth  - width;
  if (top  + depth > screenHeight) top   = screenHeight - depth;
  }



void WinPosData::rationalize() {
  if (left   <  0)       left   =   0;
  if (top    <  0)       top    =   0;
  if (width  < minWidth) width = minWidth;
  if (depth  < minDepth) depth = minDepth;
  }




#if 0
//  data.setMin(int(hDLU * hDLUtoPxls / 4.0), int(vDLU * vDLUtoPxls / 4.0));
void WinPos::setMin(RECT& rect) {
  data.setMin(int((rect.right - rect.left) / 4.0), int((rect.bottom - rect.top) / 4.0));
  }
#endif

