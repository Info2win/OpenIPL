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
    grayscale.cpp \
    image.cpp \
    jpeg.cpp \
    pixel.cpp \
    png.cpp \
    rgb.cpp \
    rgba.cpp \
    third_party/stb/stb_image.cpp \
    third_party/stb/stb_image_write.cpp

HEADERS += \
    OpenIPL_global.h \
    grayscale.h \
    image.h \
    jpeg.h \
    pixel.h \
    png.h \
    rgb.h \
    rgba.h \
    third_party/stb/stb_image.h \
    third_party/stb/stb_image_write.h

QMAKE_LFLAGS += /IMPLIB:OpenIPL.lib

# Default rules for deployment.
unix {
    target.path = /usr/lib5
}
!isEmpty(target.path): INSTALLS += target
