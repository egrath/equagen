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

class Document
{
private:
    QString m_PlainContent;
    QString m_TexTemplate;
    QString m_Name;

    SvgImage *m_Svg;
    PngImage *m_Png;

    QUuid m_Uuid;

    SettingsProvider *m_Settings;

    QString m_LastCompileErrorMessage;
    bool m_Valid;

public:
    Document( const QString &name = "", const QString &initial = "" );
    ~Document();

    void setPlainContent( const QString &content );
    const QString & plainContent() const;

    // Name of the document
    void setName( const QString &name );
    const QString & name() const;

    // Templates for embedding the LaTeX code
    void setTexTemplate( const QString &templ );
    const QString & texTemplate() const;
    void loadTexTemplateFromFile( const QString &fileName );

    // Compile Document to SVG and PNG
    bool compile();
    const QString & lastCompileError() const;

    // Get SVG/PNG Documents
    const SvgImage & svgImage() const;
    const PngImage & pngImage() const;

    // Get UUID of document
    const QUuid & uuid() const;

    // Is the current document valid? (i.e. have the PNG/SVN's generated)
    bool valid() const;
};

#endif // DOCUMENT_H
