﻿#include "PreviewScrollArea.h"

// PUBLIC
PreviewScrollArea::PreviewScrollArea( QWidget *parent ) : QScrollArea( parent )
{
    qDebug() << "PreviewScrollArea::ctor()";
    setFocusPolicy( Qt::WheelFocus );
    setMouseTracking( true );
}

PreviewScrollArea::~PreviewScrollArea()
{
    qDebug() << "PreviewScrollArea::dtor()";
}

// PROTECTED
void PreviewScrollArea::wheelEvent( QWheelEvent *event )
{
    event->accept();
    qDebug() << "PreviewScrollArea: Wheel event, emitting signal ...";

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
