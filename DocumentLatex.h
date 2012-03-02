// LaTeX Document
#ifndef DOCUMENTLATEX_H
#define DOCUMENTLATEX_H

#include "Document.h"

class DocumentLatex : public Document
{
private:
    QString m_TexTemplate;

public:
    DocumentLatex( const QString &name = "", const QString &initial = "" );
    ~DocumentLatex();

    // LaTeX Templates
    void setTexTemplate( const QString &templ );
    const QString & texTemplate() const;
    void loadTexTemplateFromFile( const QString &fileName );

    // Compile the LaTeX document
    virtual bool compile();
};

#endif // DOCUMENTLATEX_H
