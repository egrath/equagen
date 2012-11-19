#include "CommandLineParser.h"

CommandLineParser *CommandLineParser::m_Instance;

// PRIVATE
QVariant CommandLineParser::getDefaultValue( const QString &key )
{
    if( key.compare( "nogui" ) == 0 )
        return QVariant( false );
    else if( key.compare( "help" ) == 0 )
        return QVariant( false );

    throw( new QString( "no default value for given argument key" ));
}

// PUBLIC
CommandLineParser *CommandLineParser::getInstance()
{
    if( m_Instance != 0 )
        return m_Instance;

    throw( new QString( "commandline parser not initialized yet!" ));
}

CommandLineParser::CommandLineParser(int &argc, char **argv)
{
    m_ArgCount = argc;
    m_ArgVect = argv;

    m_Instance = this;

    m_Parameters = new QHash<QString,QVariant>();
}

CommandLineParser::~CommandLineParser()
{
    delete m_Parameters;
}

void CommandLineParser::parse()
{
    for( int index = 1; index < m_ArgCount; index ++ )
    {
        QString argument( m_ArgVect[index] );
        if( argument.startsWith( '-' ))
        {
            QString a = argument.right( argument.length() -1 );
            if( a.compare( "nogui" ) == 0 )
                m_Parameters->insert( "nogui", QVariant( true ));
            else if( a.compare( "help" ) == 0 )
                m_Parameters->insert( "help", QVariant( true ));
        }
    }
}

QVariant CommandLineParser::argument(const QString &key)
{
    return m_Parameters->value( key, getDefaultValue( key ));
}

QString CommandLineParser::executableName()
{
    return m_ArgVect[0];
}
