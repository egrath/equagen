#ifndef RENDERER_H
#define RENDERER_H

#include <QtGui>
#include <QtSvg>

#include "SvgImage.h"
#include "SettingsProvider.h"

class Renderer : public QWidget
{
private:
    QSvgRenderer m_Renderer;
    qreal m_Scale;

    SettingsProvider *m_Settings;

public:
    void init();
    Renderer();
    Renderer( const SvgImage &image );
    ~Renderer();

    void setImage( const SvgImage &image );

    const qreal & scale() const;
    void setScale( const qreal &scale );

protected:
    virtual void paintEvent( QPaintEvent *event );
    virtual void resizeEvent( QResizeEvent *event );
};

#endif // RENDERER_H
