#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <QtGui>
#include "MainWindow.h"

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
