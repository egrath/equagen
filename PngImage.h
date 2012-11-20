#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include <QImage>
#include <QBuffer>
#include <QUrl>
#include <QDebug>

#include "BaseImage.h"
#include "Debug.h"

class PngImage : public BaseImage
{
public:
    PngImage( const QByteArray &content );

    virtual void setOriginalSource( const OriginalSource & source );
    virtual const OriginalSource originalSource() const;
};

#endif // PNGIMAGE_H
