#include "DocumentLatex.h"

DocumentLatex::DocumentLatex(const QString &name, const QString &initial) : Document( name, initial )
{
    qDebug() << "DocumentLatex::ctor()";

    setDocumentType( DT_LATEX );
    loadTexTemplateFromFile( ":/templates/latex.template" );
}

DocumentLatex::~DocumentLatex()
{
    qDebug() << "DocumentLatex::dtor()";
}

void DocumentLatex::setTexTemplate( const QString &templ )
{
    m_TexTemplate = templ;
}

const QString & DocumentLatex::texTemplate() const
{
    return m_TexTemplate;
}

void DocumentLatex::loadTexTemplateFromFile( const QString &fileName )
{
    QFile templateFile( fileName );
    templateFile.open( QFile::ReadOnly );

    setTexTemplate( QString::fromAscii( templateFile.readAll().data() ));
    templateFile.close();
}

bool DocumentLatex::compile()
{
    qDebug() << "Document::compile";

    // Create original source structure
    OriginalSource source;
    source.Type = "latex";
    source.Template = m_TexTemplate;
    source.Source = plainContent();

    // Create temporary directory for tex commands output
    emit compilationStep( "Building representation", 10 );

    QDir tempDir( QString( "%1/eq.%2" ).arg( QDir::tempPath() ).arg( qrand() ));
    if( ! tempDir.exists() )
        tempDir.mkpath( tempDir.path() );

    // Create temporary file with content combined with template
    QString templ = QString( m_TexTemplate );
    QString cont( templ.replace( "[% equation -%]", plainContent() ));
    QFile texFile( QString( "%1/latex.tex" ).arg( tempDir.path() ));
    texFile.open( QFile::WriteOnly );
    texFile.write( cont.toStdString().c_str() );
    texFile.close();

    qDebug() << "----------- TEX FILE START --------------";
    qDebug() << cont;
    qDebug() << "----------- TEX FILE END ----------------";

    // Compile LaTeX to DVI
    emit compilationStep( "Compiling LaTex", 40 );

    QProcess cmd;
    cmd.setWorkingDirectory( tempDir.path() );
    cmd.setProcessChannelMode( QProcess::MergedChannels );

    QStringList cmdArguments;
    cmdArguments.append( "-halt-on-error" );
    cmdArguments.append( "-no-shell-escape" );
    cmdArguments.append( "latex.tex" );

    cmd.start( settingsProvider()->latexBinary(), cmdArguments );
    if( ! cmd.waitForFinished() || cmd.exitCode() != 0 )
    {
        // Error occured
        setLastCompileError( QString( cmd.readAll() ));
        throw( new QString( "Compilation failed" ));
    }

    // Convert DVI to SVG
    emit compilationStep( "Converting DVI to SVG", 80 );

    cmdArguments.clear();
    cmdArguments.append( "--output=equation.svg" );
    cmdArguments.append( "--no-fonts" );
    cmdArguments.append( "--no-style" );
    cmdArguments.append( "--exact" );
    cmdArguments.append( "--scale=2" );
    cmdArguments.append( "latex.dvi" );

    cmd.start( settingsProvider()->dvisvgmBinary(), cmdArguments );
    if( ! cmd.waitForFinished() || cmd.exitCode() != 0 )
    {
        // Error occured
        setLastCompileError( QString( cmd.readAll() ));
        throw( new QString( "Compilation failed" ));
    }

    // Read the SVG File for internal usage
    QFile svgFile( QString( "%1/equation.svg" ).arg( tempDir.path() ));
    svgFile.open( QFile::ReadOnly );
    if( m_Svg != 0 )
        delete m_Svg;
    m_Svg = new SvgImage( svgFile.readAll() );
    m_Svg->setOriginalSource( source );

    qDebug() << m_Svg->originalSource().Template;

    svgFile.close();

    // Convert the SVG to PNG
    emit compilationStep( "Converting SVG to PNG", 90 );

    QByteArray *rawPng = SvgUtils::rasterSvgToPng( *( m_Svg->rawContent() ));
    m_Png = new PngImage( *rawPng );
    m_Png->setOriginalSource( source );

    delete rawPng;

    // Remove temporary files
    QFileInfoList files = tempDir.entryInfoList();
    QFileInfoList::iterator iter = files.begin();
    while( iter != files.end() )
    {
        tempDir.remove((*iter).filePath());
        iter ++;
    }

    tempDir.rmdir( tempDir.path() );

    setDocumentValid( true );
    emit compilationStep( "Finished", 100 );

    return true;
}
