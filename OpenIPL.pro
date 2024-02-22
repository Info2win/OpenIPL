CONFIG -= qt

TEMPLATE = lib
DEFINES += OPENIPL_LIBRARY
CONFIG += create_lib
CONFIG += dll

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    image.cpp \
    jpeg.cpp \
    png.cpp

HEADERS += \
    OpenIPL_global.h \
    image.h \
    jpeg.h \
    png.h

QMAKE_LFLAGS += /IMPLIB:OpenIPL.lib

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
