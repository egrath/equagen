#ifndef MATHSYMS_H
#define MATHSYMS_H

#include <QtGui>

class MathSyms : public QWidget
{
    Q_OBJECT

private:
    void setupUserInterface();

public:
    MathSyms( QWidget *parent = 0 );
    ~MathSyms();
};

#endif // MATHSYMS_H
