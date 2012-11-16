#include "MathSyms.h"

// PRIVATE
void MathSyms::setupUserInterface()
{
    resize( 384, 640 );
    setWindowTitle( "Mathematical Symbols" );
}

// PUBLIC
MathSyms::MathSyms( QWidget *parent ) : QWidget( parent )
{
    qDebug() << "MathSyms::ctor()";
    setupUserInterface();
}

MathSyms::~MathSyms()
{
    qDebug() << "MathSyms::dtor()";
}
