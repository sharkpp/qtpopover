#-------------------------------------------------
#
# written by sharkpp
#
#-------------------------------------------------

INCLUDEPATH += $$PWD
VPATH       += $$PWD

equals(POPOVER_USE_STATIC_LIB,1) {
  CONFIG(debug,debug|release){
    win32:LIBS +=   $$PWD/../dist/debug/libPopover.lib
    unix:LIBS  += -L$$PWD/../dist/debug/ -lPopover
  } else {
    win32:LIBS +=   $$PWD/../dist/release/libPopover.lib
    unix:LIBS  += -L$$PWD/../dist/release/ -lPopover
  }
} else {
  SOURCES += popover.cpp

  HEADERS += popoverfocuser.h

  macx:SOURCES        += popoverfocuser.mm
  linux|win32:SOURCES += popoverfocuser.cpp
}

HEADERS += popover.h

macx:LIBS += -framework AppKit
