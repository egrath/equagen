#ifndef DOCUMENTCOMPILER_H
#define DOCUMENTCOMPILER_H

#include <QtCore>

#include "Debug.h"
#include "Document.h"

class DocumentCompiler : public QThread
{
    Q_OBJECT

private:
    Document *m_Document;
    bool m_FinishedWithError;
    QString m_CompilerErrorMessage;

public:
    DocumentCompiler( Document *document );
    bool finishedWithError() const;
    const QString & compilerErrorMessage() const;

    // QThread::run
    virtual void run();

public slots:
    void compilationStepHandler( const QString &message, int step );

signals:
    void compilationStep( const QString & message, int step );
};

#endif // DOCUMENTCOMPILER_H
