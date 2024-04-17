// Manage Window Position and Size


#pragma once


struct WinPosData {
int left;                     // Window coordinates in pixels
int top;
int width;
int depth;

int defWidth;                 // Width and depth when loaded
int defDepth;
int minWidth;                 // Minimums in pixels
int minDepth;


  WinPosData() : left(0), top(0), width(0), depth(0), minWidth(200), minDepth(200) { }
 ~WinPosData() { }

  WinPosData& operator= (RECT& r);

  void        set(int& cx, int& cy);

  operator RECT() {return {left, top, width, depth};}

//  void setMin(int w, int d) {minWidth = w; minDepth = d;}

  void load(RECT& defaultRect);

  void save();

  void normalize(int screenWidth, int maxDepth);

private:

  void rationalize();

  void display(TCchar* tgt, int d);
  };


class WinPos {

WinPosData data;                                  // App window position and size in pixels

double     hDLUtoPxls;                            // Factor (dlu * factore = pixels) to convert DLUs to
double     vDLUtoPxls;                            // pixelse, different for horizontal and vertical
int        defWidth;                              // Width and depth in DLUs specified in Resource File
int        defDepth;
int        screenWidth;                           // Maximum Screen width and height
int        screenHeight;

public:

  WinPos();
 ~WinPos() {save();}

  void setDLUToPxls(RECT& rect, int hDLU, int vDLU);    // Window Rectangle in pixels and
                                                        // Dialog box h&v Device Logical units
//void setMin(RECT& rect);                              // Window Rectangle in pixels
  int  dluToScreen(int dlu, bool horiz = true);

  // initialize the window to the saved position and size, only call once

  void initialPos(CWnd* wnd, RECT& defaultRect);

  void set(CRect& curPos) {data = curPos;}

  void set(int& cx, int& cy) {data.set(cx, cy);}

  RECT get() {return data;}

private:

  void save() {data.save();}                     // Save the current position and size when app closes.
  };


extern WinPos winPos;
