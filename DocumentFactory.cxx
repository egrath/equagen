#include "DocumentFactory.h"

DocumentFactory *DocumentFactory::m_Instance = 0;

// PRIVATE METHODS
DocumentFactory::DocumentFactory()
{
    qDebug() << "DocumentFactory::ctor()";
}

DocumentFactory::~DocumentFactory()
{
    if( DocumentFactory::m_Instance != 0 )
        delete m_Instance;
}

// PUBLIC
DocumentFactory * DocumentFactory::instance()
{
    if( m_Instance == 0 )
        m_Instance = new DocumentFactory();

    return m_Instance;
}

Document * DocumentFactory::createDocument( DocumentType type )
{
    switch( type )
    {
    case DT_LATEX:
        qDebug() << "DocumentFactory: Creating new LaTeX document";
        return new DocumentLatex();

    default:
        throw( new QString( "DocumentFactory: no document type specified" ));
    }

    return 0;
}
