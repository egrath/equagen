#ifndef PREVIEWSCROLLAREA_H
#define PREVIEWSCROLLAREA_H

#include <QDebug>
#include <QWheelEvent>
#include <QScrollArea>

#include "Debug.h"
#include "Renderer.h"

// Used to catch the Mouse wheel area
class PreviewScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    PreviewScrollArea( QWidget *parent = 0 );
    ~PreviewScrollArea();

protected:
    virtual void wheelEvent( QWheelEvent *event );
    virtual void mouseMoveEvent( QMouseEvent *event );
    virtual void mousePressEvent( QMouseEvent *event );
    virtual void mouseReleaseEvent( QMouseEvent *event );

signals:
    void mouseWheelEvent( QWheelEvent *event );
};


#endif // PREVIEWSCROLLAREA_H
