#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include <QDebug>
#include "ui_ProgressIndicator.h"

class ProgressIndicator : public QWidget
{
    Q_OBJECT

private:
    Ui_ProgressIndicator *m_UserInterface;

    void setupUserInterface();

public:
    ProgressIndicator( QWidget *parent = 0 );
    ~ProgressIndicator();

    void centerOnParent();
    void setStatus( const QString &text, int step );
};

#endif // PROGRESSINDICATOR_H
