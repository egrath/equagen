#ifndef TEMPLATEEDITOR_H
#define TEMPLATEEDITOR_H

#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include "ui_TemplateEditor.h"

class TemplateEditor : public QDialog
{
    Q_OBJECT

private:
    Ui_TemplateEditor *m_UserInterface;

    void setupUserInterface();

private slots:
    void buttonCancelPressed();
    void buttonSaveAndExitPressed();
    void buttonLoadDefaultPressed();

public:
    TemplateEditor( QWidget *parent = 0 );
    ~TemplateEditor();

    QString templateName() const;
    QString templateCode() const;
};

#endif // TEMPLATEEDITOR_H
