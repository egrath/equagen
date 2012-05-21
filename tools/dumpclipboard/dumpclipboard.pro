CONFIG = qt
unix {
    OBJECTS_DIR = build.tmp/linux
    DESTDIR = build/linux
}

win32 {
    CONFIG += console
    OBJECTS_DIR = build.tmp/win32
    DESTDIR = build/win32
}

SOURCES += \
    dumpclipboard.cxx
