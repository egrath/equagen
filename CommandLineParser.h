#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QString>
#include <QDebug>
#include <QHash>

#include <iostream>

#include "Debug.h"

using std::cout;
using std::endl;

class CommandLineParser
{
private:
    static CommandLineParser *m_Instance;

    int m_ArgCount;
    char **m_ArgVect;

    QHash<QString,QVariant> *m_Parameters;
    QVariant getDefaultValue( const QString &argument );

public:
    static CommandLineParser * instance();

    CommandLineParser( int &argc, char **argv );
    ~CommandLineParser();

    bool parse();
    QVariant argument( const QString &key );
    bool hasArgument( const QString &key );
    QString executableName();
};

#endif // COMMANDLINEPARSER_H
