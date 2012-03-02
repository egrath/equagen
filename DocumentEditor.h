#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include <QWheelEvent>

#include "ClipboardManager.h"
#include "DocumentLatex.h"
#include "SettingsProvider.h"

#include "ui_DocumentEditor.h"

class DocumentEditor : public QWidget
{
    Q_OBJECT

private:
    Ui_DocumentEditor *m_UserInterface;
    PreviewScrollArea *m_PreviewScrollArea;
    Renderer *m_Renderer;
    Document *m_Document;
    SettingsProvider *m_Settings;

    bool m_IsModified;
    bool m_CanCompile;
    bool m_HasError;

    ClipboardCopyType m_ClipboardCopyType;

    void setupUserInterface();

private slots:
    void textEditorTextChanged();
    void previewScrollerMouseWheelEvent( QWheelEvent *event );

public:
    DocumentEditor( DocumentType type, const QString &name = "", const QString &initialContent = "", QWidget *parent = 0 );
    ~DocumentEditor();

    const QString & compilerLog() const;

    bool compile(); // True if compile succeeds, false if not
    bool lastCompileSuccessfull() const;
    void copyImageToClipboard() const;

    bool isModified() const;
    bool canCompile() const;
    bool canCopy() const;
    bool hasError() const;

    // Document Name getter/setter
    void setName( const QString &name );
    const QString & name() const;

    // Document UUID getter
    const QUuid & uuid() const;

    // Template used by the contained Document
    void setTexTemplate( const QString &templ );

    // Type of Image for Clipboard copy
    void setClipboardCopyMode( ClipboardCopyType type );

    // Zoom operations
    qreal zoomIn();
    qreal zoomOut();
    qreal zoomNormal();

signals:
    void documentStatusChanged();
};

#endif // DOCUMENTEDITOR_H
