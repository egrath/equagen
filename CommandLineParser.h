#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <QString>
#include <QDebug>
#include <QHash>

#include <iostream>

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
    static CommandLineParser * getInstance();

    CommandLineParser( int &argc, char **argv );
    ~CommandLineParser();

    void parse();
    QVariant argument( const QString &key );
    QString executableName();
};

#endif // COMMANDLINEPARSER_H
