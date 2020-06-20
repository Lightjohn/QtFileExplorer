[![Build Status](https://travis-ci.org/Lightjohn/QtFileExplorer.svg?branch=master)](https://travis-ci.org/Lightjohn/QtFileExplorer)

Build
=====

**Note**: Will now need **Qt5.15** because of move to bin feature

you will need `qt5-default` and `qt5-qmake` on Ubuntu

`qmake` then `make -j 4`



QtFileExplorer
==============

Qt quick image visualisation.

Use Miller Columns to explore files and folder.

It support only images for now but can be improve.

Functionalities
================

*SPACE* : Launch preview mode (images only).

*ENTER* : Open the current file with os default application (every files).

*Double Clic* : If there is a double click on preview mode then the fullscreen mode is activated.

*Suppr* : Delete the folder/file selected, also work with shift selected folders/files.

**WARNING** Suppr does not move to trash, will delete recursively a folder...

The application remember the last path used and will use it on launch.   

To leave the fullscreen mode: *ESC*, *DOUBLE-CLIC*, *SPACE*

![Alt text](example2.png?raw=true "Example")
