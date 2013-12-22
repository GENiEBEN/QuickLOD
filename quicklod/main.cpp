#include "gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;
    w.setWindowFlags( Qt::Dialog );
    w.setFixedSize(w.size());
    w.setWindowTitle(QString("%1 v%2").arg(w.windowTitle()).arg(APP_VERSION));

    QString foo;
    if (QCoreApplication::arguments().count() == 2){
        foo = QCoreApplication::arguments().at(1);
        foo = foo.right(foo.length() - 1); //avoid including the argument delimiter "-" as minus sign so that -27 = 27 and --27 = -27)
    }

    if (foo != ""){
        set_amd_lod(foo);
        qApp->quit();
    } else {
        w.show();
    }
    return a.exec();
}
