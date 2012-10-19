#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QtGui>

class Template
{
private:
    QUuid m_Uuid;
    QString m_Name;
    QString m_Code;

public:
    Template( QString name, QString code );
    ~Template();

    const QUuid & uuid() const;
    const QString & name() const;
    const QString & code() const;
};

#endif // TEMPLATE_H
