#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include <QWheelEvent>

#include "ClipboardManager.h"
#include "SettingsProvider.h"
#include "DocumentFactory.h"
#include "DocumentCompiler.h"
#include "Template.h"

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
    Template m_TexTemplateInUse;
    int m_TextEditorWidth;

    bool m_IsModified;
    bool m_CanCompile;
    bool m_HasError;
    bool m_PreviewAutoscroll;

    ClipboardCopyType m_ClipboardCopyType;

    void setupUserInterface();
    void setupSplitterPane();

    QImage preparePngImageForClipboard() const;

private slots:
    void textEditorTextChanged();
    void previewScrollerMouseWheelEvent( QWheelEvent *event );
    void previewScrollerVerticalBarMoved( int value );
    void splitterPaneHandleMoved( int pos, int index );

    void configurationSettingsChanged();

    void compilationStepHandler( const QString &message, int step );

protected:
    virtual void showEvent( QShowEvent *event );
    virtual void resizeEvent( QResizeEvent *event );

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

    // Type of Image for Clipboard copy
    void setClipboardCopyMode( ClipboardCopyType type );
    const ClipboardCopyType & clipboardCopyMode() const;

    // Export document to file
    bool exportDocumentToFile( ImageType type, const QString &fileName );

    // Import document from file
    bool setDocumentFromSource( const OriginalSource &source );

    // Set the Latex Template
    void setDocumentLatexTemplate( Template t );
    Template & documentLatexTemplate();

    // Type of underlaying Document
    const DocumentType & documentType() const;

    // Set focus to the input text box
    void focusInputTextbox();

    // Zoom operations
    qreal zoomIn();
    qreal zoomOut();
    qreal zoomNormal();

signals:
    void documentStatusChanged();
    void compilationStep( const QString &message, int step );
};

#endif // DOCUMENTEDITOR_H
