#ifndef SVGIMAGE_H
#define SVGIMAGE_H

#include <QDomDocument>
#include <QTextStream>
#include <QDebug>
#include <QXmlReader>
#include <QUrl>

#include "BaseImage.h"
#include "SvgUtils.h"
#include "Debug.h"

class SvgImage : public BaseImage
{
public:
    SvgImage( const QByteArray &content );

    virtual void setOriginalSource( const OriginalSource & source );
    virtual const OriginalSource originalSource() const;
};

#endif // SVGIMAGE_H
