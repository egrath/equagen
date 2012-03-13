#include "ProgressIndicator.h"

// PRIVATE
void ProgressIndicator::setupUserInterface()
{
    m_UserInterface = new Ui_ProgressIndicator();
    m_UserInterface->setupUi( this );

    //this->setVisible( false );
}

// PUBLIC
ProgressIndicator::ProgressIndicator(QWidget *parent) : QWidget( parent )
{
    setupUserInterface();
    centerOnParent();

    setStatus( "Initializing", 0 );
}

ProgressIndicator::~ProgressIndicator()
{
    delete m_UserInterface;
}

void ProgressIndicator::centerOnParent()
{
    QSize parentSize = this->parentWidget()->size();
    QPoint newPosition;

    newPosition.setX( parentSize.width() / 2 - this->size().width() / 2 );
    newPosition.setY( parentSize.height() / 2 - this->size().height() / 2 - 100 );

    this->move( newPosition );
}

void ProgressIndicator::setStatus( const QString &text, int step )
{
    m_UserInterface->labelStatus->setText( text );
    m_UserInterface->progressBar->setValue( step );
}
