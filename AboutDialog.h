#pragma GCC diagnostic ignored "-Wunused-parameter"
#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "ui_AboutDialog.h"

class AboutDialog : public QDialog
{
    Q_OBJECT

private:
    Ui_AboutDialog *m_UserInterface;

    void setupUserInterface();

private slots:
    void buttonOkPressed( bool checked );

public:
    AboutDialog( QWidget *parent = 0 );
};

#endif // ABOUTDIALOG_H
