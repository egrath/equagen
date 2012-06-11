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
public:
    enum ImportType
    {
        IT_FILE,
        IT_CLIPBOARD
    };

private:
    QString m_File;
    OriginalSource m_Source;
    bool m_IsValid;

    bool parsePng();
    bool parseSvg();

    ImportType m_ImportType;

public:
    DocumentImporter();
    DocumentImporter( const QString &fileName );

    bool isValid() const;
    bool parse();

    DocumentType type() const;
    const OriginalSource & source() const;

    const QString & fileName() const;
};

#endif // DOCUMENTIMPORTER_H
