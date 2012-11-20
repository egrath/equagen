#include "CUIProcessor.h"

CUIProcessor::CUIProcessor(const QString &code, const QString &templ, const QString &output)
{
    m_Code = code;
    m_Template = templ;
    m_Output = output;
}

CUIProcessor::~CUIProcessor()
{
}

bool CUIProcessor::process()
{
    SettingsProvider *settings = SettingsProvider::instance();

    // Get given template or default one
    cout << "info: retrieving template: ";
    Template templ = settings->getLatexTemplate( m_Template );
    cout << "(name=" << templ.name().toStdString() << ") ... OK" << endl;

    // Build document
    cout << "info: building document: ";
    DocumentLatex doc;
    doc.setTexTemplate( templ.code() );
    doc.setPlainContent( m_Code );
    cout << "OK" << endl;

    // Compile
    cout << "info: compiling document: ";
    bool compiled = false;
    try
    {
        compiled = doc.compile();
    }
    catch( const QString * )
    {
        cout << "FAILED, see logfile below" << endl;
        m_ErrorLog = doc.lastCompileError();
        return false;
    }

    if( compiled )
    {
        QFile outputFile( m_Output );
        outputFile.open( QFile::WriteOnly );

        // Save to output
        if( m_Output.toLower().endsWith( ".png" ))
            outputFile.write( *( doc.pngImage().rawContent() ));
        else if( m_Output.toLower().endsWith( ".svg" ))
            outputFile.write( *( doc.svgImage().rawContent() ));

        outputFile.close();
        cout << "OK" << endl;
    }

    return true;
}

const QString & CUIProcessor::errorLog() const
{
    return m_ErrorLog;
}
