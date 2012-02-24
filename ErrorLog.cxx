#include "ErrorLog.h"

void ErrorLog::setupUserInterface()
{
    m_UserInterface = new Ui_ErrorLog();
    m_UserInterface->setupUi( this );

    // Connect signals
    QObject::connect( m_UserInterface->actionButtonClose, SIGNAL(triggered(bool)),this, SLOT(closeButtonPressed(bool)));
}

void ErrorLog::closeButtonPressed( bool checked )
{
    this->close();
}

ErrorLog::ErrorLog( QWidget *parent ) : QWidget( parent )
{
    setupUserInterface();
}

ErrorLog::~ErrorLog()
{
}

void ErrorLog::setMessage( const QString &message )
{
    m_UserInterface->textEditErrorLog->document()->setPlainText( message );
}
