CONFIG += testcase
TARGET = tst_qqmlinspector
macx:CONFIG -= app_bundle

SOURCES += tst_qqmlinspector.cpp

INCLUDEPATH += ../shared
include(../shared/debugutil.pri)

DEFINES += SRCDIR=\\\"$$PWD\\\"
CONFIG += parallel_test declarative_debug

QT += qml-private testlib
