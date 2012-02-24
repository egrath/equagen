#ifndef SVGIMAGE_H
#define SVGIMAGE_H

#include "BaseImage.h"

class SvgImage : public BaseImage
{
public:
    SvgImage( const QByteArray &content );
};

#endif // SVGIMAGE_H
