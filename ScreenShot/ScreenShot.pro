QT += quick
QT += gui
QT += widgets printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += /usr/lib/libKF5WindowSystem.so.5

INCLUDEPATH += /usr/include/KF5/KWindowSystem

SOURCES += \
    capture.cpp \
    filter.cpp \
    freecapture.cpp \
    longshot.cpp \
        main.cpp \
    mosaic.cpp \
    mylabel.cpp \
        recscreen.cpp \

resources.files = main.qml 
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
    capture.h \
    filter.h \
    freecapture.h \
    imgprovider.h \
    longshot.h \
    RecScreen.h \
FORMS += \
    mosaic.h \
    mylabel.h

DISTFILES += \
    MainContent.qml

FORMS += \
    filter.ui \
    form.ui \
    mosaic.ui
