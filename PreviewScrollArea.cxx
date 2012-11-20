#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "PreviewScrollArea.h"

// PUBLIC
PreviewScrollArea::PreviewScrollArea( QWidget *parent ) : QScrollArea( parent )
{
    debug() << "PreviewScrollArea::ctor()";
    setFocusPolicy( Qt::WheelFocus );
    setMouseTracking( true );
}

PreviewScrollArea::~PreviewScrollArea()
{
    debug() << "PreviewScrollArea::dtor()";
}

// PROTECTED
void PreviewScrollArea::wheelEvent( QWheelEvent *event )
{
    event->accept();
    debug() << "PreviewScrollArea: Wheel event, emitting signal ...";

    emit mouseWheelEvent( event );
}

void PreviewScrollArea::mouseMoveEvent( QMouseEvent *event )
{
}

void PreviewScrollArea::mousePressEvent( QMouseEvent *event )
{
}

void PreviewScrollArea::mouseReleaseEvent( QMouseEvent *event )
{
}
