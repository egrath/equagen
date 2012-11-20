#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QtGui>
#include "Debug.h"

class Template : public QListWidgetItem
{
private:
    QUuid m_Uuid;
    QString m_Name;
    QString m_Code;

public:
    Template();
    Template( const Template &other );
    Template( QString name, QString code );
    Template( QString name, QString code, QUuid uuid );
    ~Template();

    const QUuid & uuid() const;
    const QString & name() const;
    const QString & code() const;

    void setUuid( const QUuid &uuid );
    void setName( const QString &name );
    void setCode( const QString &code );

    // Overriden from QListWidgetItem
    virtual QString text() const;
};

Q_DECLARE_METATYPE(Template);

#endif // TEMPLATE_H
