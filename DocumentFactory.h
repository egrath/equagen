#ifndef DOCUMENTFACTORY_H
#define DOCUMENTFACTORY_H

#include <QtGui>

#include "Debug.h"
#include "Document.h"
#include "DocumentLatex.h"

class DocumentFactory
{
private:
    static DocumentFactory *m_Instance;

    DocumentFactory();
    ~DocumentFactory();

public:
    static DocumentFactory * instance();
    Document * createDocument( DocumentType type );
};

#endif // DOCUMENTFACTORY_H
