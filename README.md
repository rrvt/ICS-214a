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

## Authors

Robert R. Van Tuyl, rrvt@swde.com

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details


