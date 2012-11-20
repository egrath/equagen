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
    debug() << "MathSyms::ctor()";
    setupUserInterface();
}

MathSyms::~MathSyms()
{
    debug() << "MathSyms::dtor()";
}
