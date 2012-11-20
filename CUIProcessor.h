#ifndef CUIPROCESSOR_H
#define CUIPROCESSOR_H

#include <Qt>
#include <iostream>

#include "Debug.h"
#include "DocumentCompiler.h"
#include "DocumentFactory.h"
#include "SettingsProvider.h"
#include "Template.h"

using std::cout;
using std::endl;

class CUIProcessor
{
private:
    QString m_Code;
    QString m_Template;
    QString m_Output;

    QString m_ErrorLog;

public:
    CUIProcessor( const QString &code, const QString &templ, const QString &output );
    ~CUIProcessor();

    bool process();
    const QString & errorLog() const;
};

#endif // CUIPROCESSOR_H
