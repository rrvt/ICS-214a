

ICS_214a.chm : *.htm ICS_214a.hhp ICS_214a.hhc App.css
  -1 "C:\Program Files (x86)\HTML Help Workshop\hhc" ICS_214a


Clean.cln    :
  @echo "Cleaning"
  cd $(MAKEDIR)
  del /F ICS_214a.chm


Release/ICS_214a.chm : ICS_214a.chm
  copy $(MAKEDIR)\ICS_214a.chm  $(MAKEDIR)\..\Release\ICS_214a.chm


Release/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Release
  del ICS_214a.chm
  cd $(MAKEDIR)


Debug/ICS_214a.chm : ICS_214a.chm
  copy $(MAKEDIR)\ICS_214a.chm  $(MAKEDIR)\..\Debug\ICS_214a.chm


Debug/Clean.cln    : Clean.cln
  cd $(MAKEDIR)\..\Debug
  del ICS_214a.chm
  cd $(MAKEDIR)


Release/Rebuild.rbd : Release/Clean.cln Release/ICS_214a.chm


Debug/Rebuild.rbd   : Debug/Clean.cln Debug/ICS_214a.chm


