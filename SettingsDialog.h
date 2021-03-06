#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFontDatabase>

#include "SettingsProvider.h"
#include "TemplateEditor.h"
#include "Template.h"
#include "Debug.h"

#include "ui_SettingsDialog.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

private:
    Ui_SettingsDialog *m_UserInterface;
    SettingsProvider *m_Settings;

    void setupUserInterface();
    void setupFontTab();

    void refreshTemplateList();

private slots:
    void buttonTemplateNewPressed();
    void buttonTemplateEditPressed();
    void buttonTemplateRemovePressed();

    void buttonBrowseLatexPressed();
    void buttonBrowseDvisvgmPressed();

    void buttonTextColorPressed();
    void buttonBackgroundColorPressed();

    void buttonSavePressed();
    void buttonCancelPressed();    

    void templateListSelectionChanged();

    QString showFileOpenDialog( const QString &directory );

public:
    SettingsDialog( QWidget *parent = 0 );
    ~SettingsDialog();
};

#endif // SETTINGSDIALOG_H
