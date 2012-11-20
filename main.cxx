#pragma GCC diagnostic ignored "-Wunused-parameter"

#include <QtGui>
#include "Debug.h"
#include "MainWindow.h"
#include "CommandLineParser.h"
#include "CUIProcessor.h"

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
        // we need all parameters except template filled out
        if( parser->hasArgument( "code" ) && parser->hasArgument( "output" ))
        {
            CUIProcessor cui( parser->argument( "code" ).toString(),
                              parser->argument( "template" ).toString(),
                              parser->argument( "output" ).toString());

            if( ! cui.process() )
            {
                cout << endl;
                cout << "+-----------------------------------------------------------------+" << endl;
                cout << "| LATEX COMPILATION ERROR LOG                                     |" << endl;
                cout << "+-----------------------------------------------------------------+" << endl << endl;
                cout << cui.errorLog().toStdString() << endl;
            }
        }
        else
        {
            cout << "error: insufficient parameters for command line" << endl;
        }
    }

    // Clean up
    delete parser;

    return rc;
}

void printHelp()
{
    CommandLineParser *parser = CommandLineParser::instance();

    cout << endl;
    cout << "Equagen - LaTeX equation generator" << endl;
    cout << endl;
    cout << "usage: " << parser->executableName().toStdString() << " options" << endl;
    cout << endl;
    cout << "options: " << endl << endl;
    cout << "    -debug                    Enable Debug output" << endl;
    cout << "    -nogui                    Enable command line operation" << endl;
    cout << "    -code <string>            LaTeX Code to process" << endl;
    cout << "    -template <string>        Template name to use (omit for default)" << endl;
    cout << "    -output <string>          Write result to file (svg or png extension)" << endl;
    cout << endl;
}
