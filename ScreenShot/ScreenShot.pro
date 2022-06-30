QT += quick
QT += gui
QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qmltypes
QML_IMPORT_NAME = painteditem
QML_IMPORT_MAJOR_VERSION = 1
LIBS += /usr/lib/libKF5WindowSystem.so.5

INCLUDEPATH += /usr/include/KF5/KWindowSystem\
               painteditem

SOURCES += \
    capture.cpp \
    copypaintitem.cpp \
    filter.cpp \
    freecapture.cpp \
    gifwidget.cpp \
    longshot.cpp \
        main.cpp \
    mosaic.cpp \
    mylabel.cpp \
    painteditem.cpp \
        recscreen.cpp \
    share.cpp

resources.files =
resources.prefix = /$${TARGET}
RESOURCES += resources \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Gif.h \
    capture.h \
    copypaintitem.h \
    elementgroup.h \
    filter.h \
    freecapture.h \
    gifwidget.h \
    imgprovider.h \
    longshot.h \
    RecScreen.h \
FORMS += \
    mosaic.h \
    mylabel.h \
    painteditem.h \
    share.h

DISTFILES +=

FORMS += \
    form.ui \
    form2.ui \
    mosaic.ui
