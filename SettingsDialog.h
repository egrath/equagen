#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDebug>
#include <QFileDialog>
#include <QDir>

#include "SettingsProvider.h"
#include "ui_SettingsDialog.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

private:
    Ui_SettingsDialog *m_UserInterface;
    SettingsProvider *m_Settings;

    void setupUserInterface();

private slots:
    void buttonBrowseLatexPressed();
    void buttonBrowseDvipngPressed();
    void buttonBrowseDvisvgmPressed();

    void buttonSavePressed();
    void buttonCancelPressed();

    QString showFileOpenDialog( const QString &directory );

public:
    SettingsDialog( QWidget *parent = 0 );
    ~SettingsDialog();
};

#endif // SETTINGSDIALOG_H
