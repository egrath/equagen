#ifndef IMAGEBASE_H
#define IMAGEBASE_H

#include <QByteArray>
#include <QString>

#include "Debug.h"
#include "OriginalSource.h"

enum ImageType
{
    IT_SVG,
    IT_PNG
};

class BaseImage
{
protected:
    QByteArray *m_RawContent;

public:
    BaseImage( const QByteArray &content );
    virtual ~BaseImage();

    // Need to be implemented in derived classes
    virtual void setOriginalSource( const OriginalSource &source ) = 0;
    virtual const OriginalSource originalSource() const = 0;

    const QByteArray * rawContent() const;       
};

#endif // IMAGEBASE_H
