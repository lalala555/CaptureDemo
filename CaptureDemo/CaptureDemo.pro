QT       += core gui axcontainer multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
RC_ICONS = app.ico

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    playerdialog.cpp \
    previewthread.cpp \
    qmyselfvideo.cpp \
    settingdlg.cpp \
    videosurface.cpp

HEADERS += \
    mainwindow.h \
    playerdialog.h \
    previewthread.h \
    qmyselfvideo.h \
    settingdlg.h \
    videosurface.h

FORMS += \
    mainwindow.ui \
    playerdialog.ui \
    settingdlg.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/../../third_lib/qcap/LIB/X86/VC/ -lQCAP

INCLUDEPATH += $$PWD/../../third_lib/qcap/INC


win32: LIBS += -L$$PWD/lib/ -lMediaPlayer
win32: LIBS += -L$$PWD/lib/ -lSrodMedia

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/MediaPlayer.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libMediaPlayer.a
win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/SrodMedia.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/lib/libSrodMedia.a

RESOURCES += \
    res.qrc

DISTFILES +=
