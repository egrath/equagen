#include "Template.h"

// PRIVATE

// PUBLIC
Template::Template(QString name, QString code )
{
    m_Uuid = QUuid();
    m_Code = code;
    m_Name = name;

    qDebug() << QString( "Created new Template [{0}] with name: [{1}]" ).arg( m_Uuid.toString(), name );
}

Template::~Template()
{
}

const QUuid & Template::uuid() const
{
    return m_Uuid;
}

const QString & Template::code() const
{
    return m_Code;
}

const QString & Template::name() const
{
    return m_Name;
}
