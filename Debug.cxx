#include "Debug.h"

QString *g_DebugLog = 0;

QDebug debug()
{
    if( g_DebugLog == 0 )
        g_DebugLog = new QString();

    CommandLineParser *parser = CommandLineParser::instance();
    if( parser->hasArgument( "debug" ))
        return QDebug(QtDebugMsg);
    else
        return QDebug( g_DebugLog );
}

QString * debugLog()
{
    return g_DebugLog;
}
