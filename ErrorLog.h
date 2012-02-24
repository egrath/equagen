#pragma GCC diagnostic ignored "-Wunused-parameter"

#ifndef ERRORLOG_H
#define ERRORLOG_H

#include <QtGui>
#include "ui_ErrorLog.h"

class ErrorLog : public QWidget
{
    Q_OBJECT

private:
    Ui_ErrorLog *m_UserInterface;

    void setupUserInterface();

private slots:
    void closeButtonPressed( bool checked );

public:
    ErrorLog( QWidget *parent = 0 );
    ~ErrorLog();

    void setMessage( const QString &message );
};

#endif // ERRORLOG_H
