#include "Template.h"

// PRIVATE

// PUBLIC
Template::Template() : QListWidgetItem( "Built-in Template", 0, QListWidgetItem::UserType )
{
    m_Uuid = QUuid::createUuid();
    m_Name = "Built-in Template";

    QFile defaultTemplate( ":/templates/latex.template" );
    defaultTemplate.open( QFile::ReadOnly );
    m_Code = QString( defaultTemplate.readAll() );
    defaultTemplate.close();
}

Template::Template( const Template &other ) : QListWidgetItem( other.name(), 0, QListWidgetItem::UserType )
{
    m_Uuid = other.uuid();
    m_Code = other.code();
    m_Name = other.name();
}

Template::Template( QString name, QString code, QUuid uuid ) : QListWidgetItem( name, 0, QListWidgetItem::UserType )
{
    m_Uuid = uuid;
    m_Code = code;
    m_Name = name;

    qDebug() << QString( "Created new Template [%1] with name: [%2]" ).arg( m_Uuid.toString(), name );
}

Template::Template(QString name, QString code ) : QListWidgetItem( name, 0, QListWidgetItem::UserType )
{
    m_Uuid = QUuid::createUuid();
    m_Code = code;
    m_Name = name;

    qDebug() << QString( "Created new Template [%1] with name: [%2]" ).arg( m_Uuid.toString(), name );
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

void Template::setUuid( const QUuid &uuid )
{
    m_Uuid = uuid;
}

void Template::setName(const QString &name)
{
    setText(name);
    m_Name = name;
}

void Template::setCode( const QString &code )
{
    m_Code = code;
}

QString Template::text() const
{
    return m_Name;
}
