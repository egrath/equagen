#ifndef TEMPLATEEDITOR_H
#define TEMPLATEEDITOR_H

#include <QFile>
#include <QDebug>
#include <QMessageBox>

#include "ui_TemplateEditor.h"

#include "Debug.h"
#include "SettingsProvider.h"

class TemplateEditor : public QDialog
{
    Q_OBJECT

private:
    Ui_TemplateEditor *m_UserInterface;
    SettingsProvider *m_Settings;
    bool m_EditExisting;

    void setupUserInterface();

private slots:
    void buttonCancelPressed();
    void buttonSaveAndExitPressed();
    void buttonLoadDefaultPressed();

public:
    TemplateEditor( QWidget *parent = 0, bool editExisting = false );
    ~TemplateEditor();

    void setTemplateName( const QString &name );
    void setTemplateCode( const QString &code );
    QString templateName() const;
    QString templateCode() const;
};

#endif // TEMPLATEEDITOR_H
