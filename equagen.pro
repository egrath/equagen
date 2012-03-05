unix {
    OBJECTS_DIR = build.tmp/linux
    DESTDIR = build/linux
}

win32 {
    OBJECTS_DIR = build.tmp/win32
    DESTDIR = build/win32
    CONFIG += console
}

QT += svg

SOURCES += \
    main.cxx \
    Document.cxx \
    SvgImage.cxx \
    PngImage.cxx \
    MainWindow.cxx \
    DocumentEditor.cxx \
    Renderer.cxx \
    PlainTextEditor.cxx \
    ErrorLog.cxx \
    BaseImage.cxx \
    SettingsDialog.cxx \
    SettingsProvider.cxx \
    PreviewScrollArea.cxx \
    DocumentLatex.cxx \
    DocumentFactory.cxx

HEADERS += \
    Document.h \
    SvgImage.h \
    PngImage.h \
    MainWindow.h \
    DocumentEditor.h \
    Renderer.h \
    PlainTextEditor.h \
    ErrorLog.h \
    BaseImage.h \
    SettingsDialog.h \
    SettingsProvider.h \
    ClipboardManager.h \
    PreviewScrollArea.h \
    DocumentLatex.h \
    DocumentFactory.h

FORMS += \
    MainWindow.ui \
    DocumentEditor.ui \
    ErrorLog.ui \
    SettingsDialog.ui

RESOURCES += \
    equagen.qrc
