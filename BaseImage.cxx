#include "BaseImage.h"

BaseImage::BaseImage( const QByteArray &content )
{
    // We store it on the heap
    m_RawContent = new QByteArray( content );
}

BaseImage::~BaseImage()
{
    delete m_RawContent;
}

const QByteArray * BaseImage::rawContent() const
{
    return m_RawContent;
}
