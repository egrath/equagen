#include "DocumentCompiler.h"

DocumentCompiler::DocumentCompiler( Document *document )
{
    debug() << "DocumentCompiler::ctor()";

    m_Document = document;
    m_FinishedWithError = false;

    // Connecting signals
    QObject::connect( m_Document, SIGNAL(compilationStep(QString,int)), this, SLOT(compilationStepHandler(QString,int)));
}

bool DocumentCompiler::finishedWithError() const
{
    return m_FinishedWithError;
}

const QString & DocumentCompiler::compilerErrorMessage() const
{
    return m_CompilerErrorMessage;
}

void DocumentCompiler::run()
{
    debug() << "DocumentCompiler::run()";

    try
    {
        m_Document->compile();
    }
    catch( QString *exception )
    {
        m_FinishedWithError = true;
        m_CompilerErrorMessage = QString( *exception );

        return;
    }

    m_FinishedWithError = false;
}

void DocumentCompiler::compilationStepHandler(const QString &message, int step)
{
    debug() << "DocumentCompiler::compilationStep: " << message << " : " << step;

    // Reemit
    emit compilationStep( message, step );
}
