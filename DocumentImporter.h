#ifndef DOCUMENTIMPORTER_H
#define DOCUMENTIMPORTER_H

#include <QFile>
#include <QImage>
#include <QDebug>
#include <QUrl>
#include <QDomDocument>

#include "Document.h"
#include "OriginalSource.h"

class DocumentImporter
{
private:
    QString m_File;
    OriginalSource m_Source;
    bool m_IsValid;

    bool parsePng();
    bool parseSvg();

public:
    DocumentImporter( const QString &fileName );

    bool isValid() const;
    bool parse();

    DocumentType type() const;
    const OriginalSource & source() const;
};

#endif // DOCUMENTIMPORTER_H
