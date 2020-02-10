QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    argument.cpp \
    camera.cpp \
    function.cpp \
    functionlistwidget.cpp \
    functionmap.cpp \
    graphwidget.cpp \
    keyboardstatemap.cpp \
    main.cpp \
    mainwindow.cpp \
    meshgenerators.cpp \
    meshobject.cpp \
    openglcontroller.cpp \
    parser.cpp \
    shader.cpp \
    vao.cpp

HEADERS += \
    argument.h \
    camera.h \
    function.h \
    functionlistwidget.h \
    functionmap.h \
    graphparameters.h \
    graphwidget.h \
    keyboardstatemap.h \
    mainwindow.h \
    meshgenerators.h \
    meshobject.h \
    openglcontroller.h \
    parser.h \
    shader.h \
    vao.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/lib/ -lglew32s

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/lib/glew32s.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/lib/libglew32s.a

unix|win32: LIBS += -L$$PWD/lib/ -lOpenGL32

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

DISTFILES += \
    FragmentShader.glsl \
    VertexShader.glsl
