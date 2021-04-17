// ICS_214a.h : main header file for the ICS_214a application

#pragma once
#include "CApp.h"


class ICS_214aDoc;
class ICS_214aView;


// ICS_214a:
// See ICS_214a.cpp for the implementation of this class

class ICS_214a : public CApp {

public:

               ICS_214a() noexcept : CApp(this) { }

  virtual BOOL InitInstance();

          ICS_214aDoc*  doc()  {return (ICS_214aDoc*)  CApp::getDoc();}
          ICS_214aView* view() {return (ICS_214aView*) CApp::getView();}

  afx_msg void OnAppAbout();
  afx_msg void OnFilePrintSetup();
  afx_msg void OnHelp();

  DECLARE_MESSAGE_MAP()
  };


extern ICS_214a theApp;

inline void         invalidate() {theApp.invalidate();}
inline ICS_214aDoc*  doc()  {return theApp.doc();}
inline ICS_214aView* view() {return theApp.view();}

