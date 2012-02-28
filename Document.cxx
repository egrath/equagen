#include "Document.h"

Document::Document( const QString &name, const QString &initial )
{
    setPlainContent( initial );
    setName( name );
    loadTexTemplateFromFile( ":/templates/equation.template" );
    m_Svg = 0;
    m_Png = 0;
    m_Valid = false;
    m_Settings = SettingsProvider::getInstance();

    // Generate a uuid for this document
    m_Uuid = QUuid::createUuid();
    qDebug() << "Document with Name: " << name << " has the UUID: " << m_Uuid.toString();
}

Document::~Document()
{
}

void Document::setPlainContent( const QString &content )
{
    m_PlainContent = content;

    qDebug() << "Document::setPlainContent";
}

const QString & Document::plainContent() const
{
    return m_PlainContent;
}

void Document::setName( const QString &name )
{
    m_Name = name;
}

const QString & Document::name() const
{
    return m_Name;
}

void Document::setTexTemplate( const QString &templ )
{
    m_TexTemplate = templ;
}

const QString & Document::texTemplate() const
{
    return m_TexTemplate;
}

void Document::loadTexTemplateFromFile( const QString &fileName )
{
    QFile templateFile( fileName );
    templateFile.open( QFile::ReadOnly );

    setTexTemplate( QString::fromAscii( templateFile.readAll().data() ));
    templateFile.close();              
}

bool Document::compile()
{
    qDebug() << "Document::compile";

    // Create temporary directory for tex commands output
    QDir tempDir( QString( "%1/eq.%2" ).arg( QDir::tempPath() ).arg( qrand() ));
    if( ! tempDir.exists() )
        tempDir.mkpath( tempDir.path() );

    // Create temporary file with content combined with template
    QString templ = QString( m_TexTemplate );
    QString plainContent( templ.replace( "[% equation -%]", m_PlainContent ));
    QFile texFile( QString( "%1/equation.tex" ).arg( tempDir.path() ));
    texFile.open( QFile::WriteOnly );
    texFile.write( plainContent.toStdString().c_str() );
    texFile.close();

    // Compile LaTeX to DVI
    QProcess cmd;
    cmd.setWorkingDirectory( tempDir.path() );
    cmd.setProcessChannelMode( QProcess::MergedChannels );

    QStringList cmdArguments;
    cmdArguments.append( "-halt-on-error" );
    cmdArguments.append( "-no-shell-escape" );
    cmdArguments.append( "equation.tex" );

    cmd.start( m_Settings->latexBinary(), cmdArguments );
    if( ! cmd.waitForFinished() || cmd.exitCode() != 0 )
    {
        // Error occured
        m_LastCompileErrorMessage = QString( cmd.readAll() );
        throw( new QString( "Compilation failed" ));
    }

    // Convert DVI to PNG
    cmdArguments.clear();
    cmdArguments.append( "-q" );
    cmdArguments.append( "-bg" );
    cmdArguments.append( "Transparent" );
    cmdArguments.append( "-T" );
    cmdArguments.append( "tight" );
    cmdArguments.append( "-D" );
    cmdArguments.append( "150" );
    cmdArguments.append( "-o" );
    cmdArguments.append( "equation.png" );
    cmdArguments.append( "equation.dvi" );

    cmd.start( m_Settings->dvipngBinary(), cmdArguments );
    if( ! cmd.waitForFinished() || cmd.exitCode() != 0 )
    {
        // Error occured
        m_LastCompileErrorMessage = QString( cmd.readAll() );
        throw( new QString( "Compilation failed" ));
    }

    // Convert DVI to SVG
    cmdArguments.clear();
    cmdArguments.append( "--output=equation.svg" );
    cmdArguments.append( "--no-fonts" );
    cmdArguments.append( "--scale=2" );
    cmdArguments.append( "equation.dvi" );

    cmd.start( m_Settings->dvisvgmBinary(), cmdArguments );
    if( ! cmd.waitForFinished() || cmd.exitCode() != 0 )
    {
        // Error occured
        m_LastCompileErrorMessage = QString( cmd.readAll() );
        throw( new QString( "Compilation failed" ));
    }

    // Read resulting files to build internal representation
    QFile pngFile( QString( "%1/equation.png" ).arg( tempDir.path() ));
    pngFile.open( QFile::ReadOnly );
    if( m_Png != 0 )
        delete m_Png;
    m_Png = new PngImage( pngFile.readAll() );
    pngFile.close();

    QFile svgFile( QString( "%1/equation.svg" ).arg( tempDir.path() ));
    svgFile.open( QFile::ReadOnly );
    if( m_Svg != 0 )
        delete m_Svg;
    m_Svg = new SvgImage( svgFile.readAll() );
    svgFile.close();

    // Remove temporary files
    QFileInfoList files = tempDir.entryInfoList();
    QFileInfoList::iterator iter = files.begin();
    while( iter != files.end() )
    {
        tempDir.remove((*iter).filePath());
        iter ++;
    }

    tempDir.rmdir( tempDir.path() );

    m_Valid = true;
    return true;
}

const QString & Document::lastCompileError() const
{
    return m_LastCompileErrorMessage;
}

const PngImage & Document::pngImage() const
{
    return *m_Png;
}

const SvgImage & Document::svgImage() const
{
    return *m_Svg;
}

const QUuid & Document::uuid() const
{
    return m_Uuid;
}

bool Document::valid() const
{
    return m_Valid;
}
