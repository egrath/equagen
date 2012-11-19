#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <QtGui>
#include "MainWindow.h"
#include "CommandLineParser.h"

void printHelp();

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    CommandLineParser *parser = new CommandLineParser( argc, argv );
    parser->parse();

    int rc = 0;
    if( parser->argument( "help" ).toBool() )
    {
        // help requested
        printHelp();
        return 0;
    }
    else if( ! parser->argument( "nogui" ).toBool())
    {
        // gui mode
        MainWindow mainWindow;
        mainWindow.show();

        rc = app.exec();
    }
    else
    {
        // command line mode
    }

    // Clean up
    delete parser;

    return rc;
}

void printHelp()
{
    CommandLineParser *parser = CommandLineParser::getInstance();

    cout << endl;
    cout << "Equagen - LaTeX equation generator" << endl;
    cout << endl;
    cout << "usage: " << parser->executableName().toStdString() << " options" << endl;
    cout << endl;
    cout << "options: " << endl << endl;
    cout << "    -nogui                    Enable command line operation" << endl;
    cout << "    -code <string>            LaTeX Code to process" << endl;
    cout << "    -template <string>        Template name to use (omit for default)" << endl;
    cout << "    -output <string>          Write result to file (svg or png extension)" << endl;
    cout << endl;
}
