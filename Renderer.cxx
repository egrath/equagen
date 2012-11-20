#pragma GCC diagnostic ignored "-Wunused-parameter"
#include "Renderer.h"

void Renderer::init()
{
    m_Settings = SettingsProvider::instance();

    // Set configured preview scale
    setScale( m_Settings->previewScale() );

    setMouseTracking( true );
}

Renderer::Renderer()
{
    init();
}

Renderer::Renderer( const SvgImage &image )
{
    init();
    setImage( image );
}

Renderer::~Renderer()
{
}

void Renderer::setImage( const SvgImage &image )
{
    m_Renderer.load( *( image.rawContent() ));

    // Set scale again from configuration (in case someone changed our settings)
    setScale( m_Scale );
}

// Set the scale of our rendering - per default we use 1.0, but this is user
// configurable
void Renderer::setScale( const qreal &scale )
{
    debug() << "Renderer::setScale: to " << scale;
    m_Scale = scale;

    // Set new size of our rendering
    this->setMinimumSize( m_Renderer.viewBoxF().width() * m_Scale + 16, m_Renderer.viewBoxF().height() * m_Scale + 16 );
    this->setMaximumSize( m_Renderer.viewBoxF().width() * m_Scale + 16, m_Renderer.viewBoxF().height() * m_Scale + 16 );
    this->resize( m_Renderer.viewBoxF().width() * m_Scale + 4, m_Renderer.viewBoxF().height() * m_Scale + 4 );

    debug() << "Renderer: got new image to render with dimension of " << m_Renderer.viewBoxF().width() << " x " << m_Renderer.viewBoxF().height() << "(excluding scale of " << m_Scale << ")";
    debug() << "    final rendering size is: " << m_Renderer.viewBoxF().width() * m_Scale << " x " << m_Renderer.viewBoxF().height() * m_Scale;
    debug() << "    minimum widget size: " << this->minimumSize();
    debug() << "    maximum widget size: " << this->maximumSize();

    // Redraw
    repaint();
}

const qreal & Renderer::scale() const
{
    return m_Scale;
}

QSize Renderer::renderedSize() const
{
    QSize size;

    size.setWidth( m_Renderer.viewBox().width() * m_Scale );
    size.setHeight( m_Renderer.viewBox().height() * m_Scale );

    return size;
}

// PROTECTED
void Renderer::paintEvent( QPaintEvent *event )
{
    event->accept();

    QPainter painter( this );

    // Fill everything white
    painter.fillRect( 0, 0, this->width(), this->height(), QBrush( QColor( 255, 255, 255 )));

    // Render the SVG with the configured scale
    if( m_Renderer.isValid() )
    {
        m_Renderer.render( &painter, QRectF( 8, 8, m_Renderer.viewBoxF().width() * m_Scale, m_Renderer.viewBoxF().height() * m_Scale ));
    }
}

void Renderer::resizeEvent( QResizeEvent *event )
{
    debug() << "Renderer: got resize to: " << event->size() << " (excluding scale of " << m_Scale << ")";
    QWidget::resizeEvent( event );
}

void Renderer::mouseMoveEvent( QMouseEvent *event )
{
}

void Renderer::mousePressEvent( QMouseEvent *event )
{
}

void Renderer::mouseReleaseEvent( QMouseEvent *event )
{
}
