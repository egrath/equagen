#ifndef TEMPLATEEDITOR_H
#define TEMPLATEEDITOR_H

#include <QFile>
#include <QDebug>
#include <QMessageBox>

#include "ui_TemplateEditor.h"

#include "SettingsProvider.h"

class TemplateEditor : public QDialog
{
    Q_OBJECT

private:
    Ui_TemplateEditor *m_UserInterface;
    SettingsProvider *m_Settings;

    void setupUserInterface();

private slots:
    void buttonCancelPressed();
    void buttonSaveAndExitPressed();
    void buttonLoadDefaultPressed();

public:
    TemplateEditor( QWidget *parent = 0 );
    ~TemplateEditor();

    void setTemplateName( const QString &name );
    void setTemplateCode( const QString &code );
    QString templateName() const;
    QString templateCode() const;
};

#endif // TEMPLATEEDITOR_H
