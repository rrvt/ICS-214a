# ICS_214a

An ICS-214 is an Activity Log. It's original intention was to record the activity of a single event.
Furthermore, the individual activities were only noted at the beginning of the activity, that is, the
start time was recorded by the end time was not.

Clearly, during this pandemic we are constrained to stay within safe boundaries.
This prevents most of us going to some activity with numbers of people in attendance.
So our activities become little things over the course of weeks or months.
The purpose of this application is to allow capturing the time spent on each of these little
activities over the course of a long period (e.g. a month). The application captures the start time,
end time and a comment on the activity. During the display of the log, the total time is
computed and displayed.

The operation is fairly straight forward:

 - When the application starts it requests that a file be loaded
 - When an activity is to start, the 2nd toolbar icon (Activity Icon activity or motion symbol)
is selected to enter the date, time and acitivity description
 - When an activity is to be completed, the 3rd toolbar icon (Stop Activity Icon stop activity icon)
is selected to add an end time to one of the unfinished activities (if there are more than one)

The first toolbar icon (Header Icon page with header) allows one to edit the header and footer
information. The fourth toolbar icon (Edit Activity Icon activity with astick or star) allows any
log entry to be edited. The fifth toolbar (New Log Icon fresh document) icon allows one to create a
new Activity Log File and supply the header and footer information. The sixth toolbar icon (Open Log
Icon opening folder) allows another log file to be opened. The seventh toolbar icon (Save Log Icon
floppy disk) will allow one to store the current log somewhere else. The eight toolbar icon (Printer
Icon printer) allows one to print the current log data.

Between invocations of the application the last activity log will be presented to the user to load
when starting the application. Times and dates will be supplied in the dialog boxes when they are
started. The dates and times are editable. The dates and times are monitored to ensure that they are
legal dates and times. Furthermore they are normalized so no matter how they are input they will
always have the same form (i.e. 01/02/20 for dates, 01:02 for times). Commas and quotes are handled
correctly within strings. End dates most often are on the same day as the start time but provisions
are made so that they may be on later times. Long descriptions are wrapped nicely most of the time
when printed.

## Getting Started

The ".msi" file will install the application on a Win7 and higher machine.  The application will appear
in the Start Menu and on the desktop.  When the application is first opened the user will need to find
a place to put the log (e.g. June.csv) files and name the file.  Backups are created each time the
application loads a particular file (up to 10 backups).

### Prerequisites

Running the application does not require any prerequisites except Win7 or above.

Building the application will.  It was built on Win7 with Visual Studio (C++ compiler) 2017.  The Wix
install compiler and Help Workshop (an old application but still available) are needed to create the
installer and help files.  My WixApp might be useful for creating the Product.wxs file if there are big
changes to the app.

Recently it has become clear that not all computers are built equally.  The application requires the
MFC redistributable which comes in a package that is sometimes not loaded into a computer.  It may be
retrieved from a Microsoft page for the redistributables:

    https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads

The following paragraph is found at that link:

    Visual Studio 2015, 2017 and 2019

    Download the Microsoft Visual C++ Redistributable for Visual Studio 2015, 2017 and 2019. The
    following updates are the latest supported Visual C++ redistributable packages for Visual Studio
    2015, 2017 and 2019. Included is a baseline version of the Universal C Runtime see MSDN for details.

        x86: vc_redist.x86.exe

        x64: vc_redist.x64.exe

        ARM64: vc_redist.arm64.exe

    Note Visual C++ 2015, 2017 and 2019 all share the same redistributable files.

Go to the web site and convince yourself that it is legitimate and download the x86 and/or the x64 version of the redistributable, which will depend on your operating systems bit size (32/64).

## Updates

### Update 1/4/21

The structure of the library was modified over the last few months which changed the way
output to the display and printer are performed.

Library Changes:
  * CApp includes a function to identify the application to Windows.
  * CApp requires the application's "this" pointer at initialization.
  * CApp includes inline functions for retrieving a pointer to the document object and view object
  * The library now contains logic to manage the actual size of fonts on the display and printed page.
  * Before the font point size was expressed as an integer 10 x font size (e.g. 120).  Now it is
    expressed as as a decimal number of the actual point size (eg. 12.0).
  * ManipT used during output was changed to remove a memory leak.
  * The Options feature was moved to the Extras and Library.  The options include an option to adjust
    the scale of the displayed and printed output.

### Update 9/10/20
Library improvement project.  Changed the Expandable Array classes, added templates for a pointer only
class in the ExpandableP class definition.  It turned out I was defining this RcdPtr class many times
worrying about exactly how it should be defined.  So I turned it into a template, which of course then
I needed to go back and add it to all the programs.  Severl iterations later I added some documentation
and I am uploading the programs today.

### August 15, 2020

Update some code.

### July 19, 2020

A recent inquiry led to adding some information in the Prerequisites section on the Visual Studio
redistributables.  The program was compiled without the MFC library loaded in the program to keep it
relatively small.  Unfortanately it must be available as a dll in order for the program to execute.

### July 16, 2020

I tried to change the print spooler job title from Untitled to something useful and failed.  It appears
that the CView class implements the call to set the title (i.w. StartDoc) and CView doesn't provide a
way to set the value before StartDoc is called.  So instead I added comments the CScrView which is
sub-classed from CScrollView (which is sub-classed from CView).

### July 15, 2020

Whoa, what have I taken on.  Windows MFC makes things a little more confusing than it should be...

Enough complaining.  The goal of this update is to figure out how to:
 - Wrap the long lines correctly
 - Count the number of lines that will fit on a single printed page with whatever printer is used
   (Apparently it matters).
 - Correctly count the number of pages

After trying and rejecting several approaches it takes three passes over the data to correctly determine
the parameters.  The first pass sends to the printer control logic very short lines and counts them
until the next line would exceed the bottom boundary as determined by the page dimensions and the margins
which the user has requested.  The second pass over the data uses the tabbing and width of the page and
margins to determine the wrap of the description.  This second pass is done in the output to the device
so that it is device dependent.  The third pass is to paginate the report, send the paginated report to
the device and count the pages (this seemed easier than just counting lines in the data as very little
additional software was required).  Finally with the number of lines per page determined, the individual
records wrapped so that the information is visible on the page and the number of pages known then the data
is output to the device.  Note, there are two devices available, the print preview and the current
printer.  While the two devices share attributes, they are output in very different ways...

### July 10, 2020

 - Chased down some bugs
 - Added the ability to change the print and print preview margins
 - Changed the right most fields in the header to float to the right edge of the output window (Display,
Print Preview or Printed Output).  The motivation is to give the maximum space for data in the header
fields.

### July 6, 2020

 - Added logic to prevent a crash when window is narrowed.
 - Add numbers on the field names
 - Merged Unit Leader Name and Position on output.  Values are input in separate fields and output to
Excel in separate fields.

### July 5, 2020

Lowell made some astute comments about the Excel spreadsheet that resulted from the csv output.  So the
following changes were made (at the moment they are option one [Tools/Options]).
 - The header was rearranged to a vertical format with the data in the description column
 - The footer was rearranged to a vertical format with the data in the description column
 - The end date was supplied for all activities, even those that have no end time

In addition when attempting to save a file, windows sometimes prevents over writing a file being used by
another program.  Detect and report an occurrence of this phenomenon.

Added a little logic to invoke the OnNewLog function at the first time startup.  Added titles to all
of the open/save dialog boxes that specify why the file name is being sought.

### July 4, 2020

Separated the command to produce a csv file for Excel and the reading and writing to the raw data.  Gave
the raw data file a unique extension (i.e. "214") while the Excel file has the traditional "csv"
extension.

While writing the help file found that a couple of the dialog boxes could be improved.  The Edit Activity
dialog can now edit more than one activity line without leaving the dialog box.  Furthermore, the
handling of dates and times was added to two of the dialog boxes where it have been neglected.

The help file was expanded to include all the operations that can be performed.  Individual pages were
written for the 4 main steps of managing an Activity with pictures of the actual dialog boxes.

## Authors

Robert R. Van Tuyl, romeo romeo victor tango alpha tango sam whisky delta echo dot charlie oscar mike

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


