#ifndef DOCUMENTEDITOR_H
#define DOCUMENTEDITOR_H

#include <QClipboard>
#include "Document.h"
#include "ui_DocumentEditor.h"

class DocumentEditor : public QWidget
{
    Q_OBJECT

private:
    Ui_DocumentEditor *m_UserInterface;
    Renderer *m_Renderer;
    Document *m_Document;

    bool m_IsModified;
    bool m_CanCompile;
    bool m_HasError;

    void setupUserInterface();

private slots:
    void textEditorTextChanged();

public:
    DocumentEditor( const QString &name = "", const QString &initialContent = "", QWidget *parent = 0 );
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

signals:
    void documentStatusChanged();
};

#endif // DOCUMENTEDITOR_H
