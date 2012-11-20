#include "CommandLineParser.h"

CommandLineParser *CommandLineParser::m_Instance;

// PRIVATE
QVariant CommandLineParser::getDefaultValue( const QString &key )
{
    if( key.compare( "nogui" ) == 0 )
        return QVariant( false );
    else if( key.compare( "help" ) == 0 )
        return QVariant( false );
    else if( key.compare( "code" ) == 0 )
        return QVariant( "" );
    else if( key.compare( "template" ) == 0 )
        return QVariant( "Built-in Template" );
    else if( key.compare( "output" ) == 0 )
        return QVariant( "" );
    else if( key.compare( "debug" ) == 0 )
        return QVariant( false );

    throw( new QString( "no default value for given argument key" ));
}

// PUBLIC
CommandLineParser *CommandLineParser::instance()
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

bool CommandLineParser::parse()
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
            else if( a.compare( "debug" ) == 0 )
                m_Parameters->insert( "debug", QVariant( true ));
            else if( a.compare( "code" ) == 0 )
            {
                // Need 1 argument
                if( m_ArgCount > index+1 && ! QString( m_ArgVect[index+1] ).startsWith( '-' ))
                    m_Parameters->insert( "code", QString( m_ArgVect[index+1] ));
                else
                {
                    cout << "error: no parameter given for option \'code\'" << endl;
                    return false;
                }
            }
            else if( a.compare( "template" ) == 0 )
            {
                // Need 1 argument
                if( m_ArgCount > index+1 && ! QString( m_ArgVect[index+1] ).startsWith( '-' ))
                    m_Parameters->insert( "template", QString( m_ArgVect[index+1] ));
                else
                {
                    cout << "error: no parameter given for option \'template\'" << endl;
                    return false;
                }
            }
            else if( a.compare( "output" ) == 0 )
            {
                // Need 1 argument
                if( m_ArgCount > index+1 && ! QString( m_ArgVect[index+1] ).startsWith( '-' ))
                {
                    QString parameterArg = QString( m_ArgVect[index+1] );
                    if( parameterArg.toLower().endsWith( ".png" ) ||
                        parameterArg.toLower().endsWith( ".svg" ))
                    {
                        m_Parameters->insert( "output", QString( m_ArgVect[index+1] ));
                    }
                    else
                    {
                        cout << "error: only png and svg output format is supported" << endl;
                        return false;
                    }
                }
                else
                {
                    cout << "error: no parameter given for option \'output\'" << endl;
                    return false;
                }
            }
        }
    }

    return true;
}

QVariant CommandLineParser::argument(const QString &key)
{
    return m_Parameters->value( key, getDefaultValue( key ));
}

bool CommandLineParser::hasArgument( const QString &key )
{
    return m_Parameters->keys().contains( key );
}

QString CommandLineParser::executableName()
{
    return m_ArgVect[0];
}
