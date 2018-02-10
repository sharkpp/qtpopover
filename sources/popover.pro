#-------------------------------------------------
#
# Project created by QtCreator 2018-01-27T18:33:11
#
#-------------------------------------------------

QT      += widgets
QT      -= gui

TARGET   = Popover
TEMPLATE = lib
CONFIG  += staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(popover.pri)

unix {
    target.path = /usr/lib
    INSTALLS += target
}

#################################################
# POST BUILD ACTION:
#   copy the build library to the dist directory
#################################################

CONFIG(debug,  debug|release) {
  DIST_DIR = $$shell_path($${PWD}/../dist/debug)
} else {
  DIST_DIR = $$shell_path($${PWD}/../dist/release)
}

defineReplace(copyToDistDir) {
    return($(COPY_FILE) $$shell_path($$shadowed($${PWD})/$$1) $$DIST_DIR)
}

post_build_cmd += \
  "$(MKDIR) $$DIST_DIR"        \
  "$$copyToDistDir($(TARGET))"

QMAKE_POST_LINK = @
for(t, post_build_cmd) {
  QMAKE_POST_LINK += $$t ;
}

