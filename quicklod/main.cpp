#include "gui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gui w;
    w.setWindowFlags( Qt::Dialog );
    w.setFixedSize(w.size());
    w.setWindowTitle(QString("%1 v%2").arg(w.windowTitle()).arg(APP_VERSION));
    w.show();

    return a.exec();
}
