// Utilities


#pragma once


String addTab(String& s, int max);

String normalizeDate(TCchar* date);
String normalizeTime(TCchar* time);


String getDateNow();
String getTimeNow();

// Display a string of no more than noChars.  If more, the insert noTabs and no more than noChars until
// string exhausted.  returns number of lines output

//int   dsplyWrap(TCchar* p, int noChars, int noTabs);
