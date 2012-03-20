#include <iostream>

#include <QApplication>
#include <QClipboard>
#include <QDebug>
#include <QMimeData>
#include <QStringList>
#include <QFile>

using std::cout;
using std::cin;
using std::endl;

int main( int argc, char **argv )
{
    QApplication app( argc, argv );

    QClipboard *clipboard = QApplication::clipboard();
    const QMimeData *data = clipboard->mimeData();

    QStringList formats = data->formats();
    QStringList::iterator iter = formats.begin();
    int id = 1;

    while( iter != formats.end() )
    {
        cout << "(" << id++ << "): " << (*iter).toStdString() << endl;
        iter++;
    }

    cout << endl << "Which one to save? ";
    cin >> id;

    QFile dump( "dump.bin" );
    dump.open( QFile::WriteOnly );
    dump.write( data->data( formats.at( id-1 )));
    dump.close();

    cout << "Written to dump.bin" << endl;
}

