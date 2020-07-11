// Vertical Display Management


#include "stdafx.h"
#include "VertMgmt.h"

#include "MessageBox.h"


VertMgmt::VertMgmt() : y(0), yMax(0), chHeight(1), maxHeight(0), uLineDelta(0), botEdge(0),
                       topMgn(0), botMgn(0), topBnd(0), botBnd(0), beginPage(false), endPage(false),
                       noLines(0), maxLines(0) { }


void VertMgmt::setAttributes(int height, double topMargin, double botMargin) {
  botEdge = height; topMgn = topMargin; botMgn = botMargin; initY();
  }


void VertMgmt::setTopMargin(double v) {topMgn = v;  initY();}
void VertMgmt::setBotMargin(double v) {botMgn = v;  initY();}


static int bufX = 0;
static int endBuf[10] = {0};


void VertMgmt::setBottom()  {
  if (y < botBnd) {
    y = botBnd;

    endBuf[bufX] = y;

    if (bufX > 0) {
      if (endBuf[bufX-1] != endBuf[bufX]) {
        String s;  s.format(_T("Whoops %i: %i, %i"), bufX, endBuf[bufX-1], endBuf[bufX]);
        int x = 1;  messageBox(s);
        }
      }
    if (++bufX >= noElements(endBuf)) bufX = 0;
    }
  }


void VertMgmt::setHeight(CDC* dc) {
TEXTMETRIC metric;

  if (dc->GetTextMetrics(&metric)) {

    chHeight = metric.tmHeight + metric.tmExternalLeading + 2;

    if (chHeight > maxHeight) maxHeight = chHeight;

    uLineDelta = chHeight - metric.tmInternalLeading - metric.tmExternalLeading;
    }
  }


void VertMgmt::lf(bool printing, bool footer) {
  if (printing && !footer) {
    if (exceedsBnd(1)) {endPage = true; return;}
    if (noLines > maxLines) maxLines = noLines;
    }

  y += maxHeight;   maxHeight = chHeight;   setMaxY(y);   noLines++;
  }


void VertMgmt::initY() {
  topBnd = y = int(topMgn * chHeight);  botBnd = int(botEdge - botMgn * chHeight);
  }

