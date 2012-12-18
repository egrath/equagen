## custom settings for output files depending on build configuration
## and os target
unix {
    OBJECTS_DIR = build.tmp/linux
    MOC_DIR = build.tmp/linux

    debug {
        DESTDIR = build/linux/debug
    }

    release {
        DESTDIR = build/linux/release
    }
}

win32 {
    OBJECTS_DIR = build.tmp/win32
    MOC_DIR = build.tmp/win32
    debug {
        DESTDIR = build/win32/debug
        CONFIG += console
    }
    release {
        DESTDIR = build/win32/release
        CONFIG -= console
    }

    CONFIG -= console
}

CONFIG += exceptions
QT += svg xml

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
    DocumentFactory.cxx \
    SvgUtils.cxx \
    ProgressIndicator.cxx \
    DocumentCompiler.cxx \
    DocumentImporter.cxx \
    AboutDialog.cxx \
    TemplateEditor.cxx \
    Template.cxx \
    MathSyms.cxx \
    CommandLineParser.cxx \
    CUIProcessor.cxx \
    Debug.cxx

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
    DocumentFactory.h \
    SvgUtils.h \
    ProgressIndicator.h \
    DocumentCompiler.h \
    OriginalSource.h \
    DocumentImporter.h \
    AboutDialog.h \
    TemplateEditor.h \
    Template.h \
    MathSyms.h \
    CommandLineParser.h \
    CUIProcessor.h \
    Debug.h

FORMS += \
    MainWindow.ui \
    DocumentEditor.ui \
    ErrorLog.ui \
    SettingsDialog.ui \
    ProgressIndicator.ui \
    AboutDialog.ui \
    TemplateEditor.ui

RESOURCES += \
    equagen.qrc

OTHER_FILES += \
    templates/latex.template \
    templates/mathsyms.txt
