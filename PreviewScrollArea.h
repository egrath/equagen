#ifndef PREVIEWSCROLLAREA_H
#define PREVIEWSCROLLAREA_H

#include <QDebug>
#include <QWheelEvent>
#include <QScrollArea>

// Used to catch the Mouse wheel area
class PreviewScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    PreviewScrollArea( QWidget *parent = 0 );
    ~PreviewScrollArea();

protected:
    virtual void wheelEvent( QWheelEvent *event );

signals:
    void mouseWheelEvent( QWheelEvent *event );
};


#endif // PREVIEWSCROLLAREA_H
