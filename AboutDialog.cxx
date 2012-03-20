#include "AboutDialog.h"

void AboutDialog::setupUserInterface()
{
    m_UserInterface = new Ui_AboutDialog();
    m_UserInterface->setupUi( this );

    QObject::connect( m_UserInterface->actionButtonOk, SIGNAL(triggered(bool)), this, SLOT(buttonOkPressed(bool)));
}

void AboutDialog::buttonOkPressed( bool checked )
{
    this->close();
}

AboutDialog::AboutDialog( QWidget *parent ) : QDialog( parent )
{
    setupUserInterface();
}
