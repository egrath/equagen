#ifndef PNGIMAGE_H
#define PNGIMAGE_H

#include "BaseImage.h"

class PngImage : public BaseImage
{
public:
    PngImage( const QByteArray &content );
};

#endif // PNGIMAGE_H
