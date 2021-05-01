QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(./googletest/gtest_dependency.pri)

CONFIG += c++11

SOURCES += \
    gtest.cpp \
    main.cpp \
    mainwindow.cpp \
    trojanmap.cpp

HEADERS += \
    mainwindow.h \
    trojanmap.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=
