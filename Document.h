#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <Qt>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDir>
#include <QProcess>
#include <QUuid>

#include "SettingsProvider.h"
#include "SvgImage.h"
#include "PngImage.h"

enum DocumentType
{
    DT_LATEX,
    DT_SKETCH,
    DT_INVALID
};

class Document
{
private:
    QString m_PlainContent;
    QString m_Name;

    QUuid m_Uuid;

    SettingsProvider *m_Settings;

    QString m_LastCompileErrorMessage;
    bool m_Valid;

    DocumentType m_DocType;

protected:
    SvgImage *m_Svg;
    PngImage *m_Png;

    void setLastCompileError( const QString &error );
    void setDocumentValid( bool documentValid );
    void setDocumentType( DocumentType type );

    SettingsProvider * settingsProvider();

public:
    Document( const QString &name = "", const QString &initial = "" );
    ~Document();

    void setPlainContent( const QString &content );
    const QString & plainContent() const;

    // Name of the document
    void setName( const QString &name );
    const QString & name() const;

    // Compile Document to SVG and PNG
    virtual bool compile() = 0;
    const QString & lastCompileError() const;

    // Get SVG/PNG Documents
    const SvgImage & svgImage() const;
    const PngImage & pngImage() const;

    // Get UUID of document
    const QUuid & uuid() const;

    // Is the current document valid? (i.e. have the PNG/SVN's generated)
    bool documentValid() const;

    // Get the type of the current Document
    const DocumentType & documentType() const;
};

#endif // DOCUMENT_H
