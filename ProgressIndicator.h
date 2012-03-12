#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include "ui_ProgressIndicator.h"

class ProgressIndicator : public QWidget
{
    Q_OBJECT

private:
    Ui_ProgressIndicator *m_UserInterface;

    void setupUserInterface();
    void centerOnParent();

public:
    ProgressIndicator( QWidget *parent = 0 );
    ~ProgressIndicator();

    void setStatus( const QString &text, int step );
};

#endif // PROGRESSINDICATOR_H
