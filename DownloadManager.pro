QT = core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += \
    mainwindow.h \
    downloaderwidget.h \
    downloadertable.h \
    downloaderitemdelegate.h \
    newdownloaddialog.h \
    downloadprogresssingleconnect.h

SOURCES += \
    mainwindow.cpp \
    main.cpp \
    downloaderwidget.cpp \
    downloadertable.cpp \
    downloaderitemdelegate.cpp \
    newdownloaddialog.cpp \
    downloadprogresssingleconnect.cpp

RESOURCES += \
    icons.qrc
