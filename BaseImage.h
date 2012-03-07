#ifndef IMAGEBASE_H
#define IMAGEBASE_H

#include <QByteArray>

enum ImageType
{
    IT_SVG,
    IT_PNG
};

class BaseImage
{
private:
    QByteArray *m_RawContent;

public:
    BaseImage( const QByteArray &content );
    virtual ~BaseImage();

    const QByteArray * rawContent() const;
};

#endif // IMAGEBASE_H
