#include "trace.h"
#include "window.h"
#include <QtGui/QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    qtTrace() << "Command line:" << app.arguments().join(" ");

    Window w;
#ifdef Q_OS_SYMBIAN
    w.showMaximized();
#else
    w.show();
#endif

    const int r = app.exec();
    qtTrace() << "App exiting" << r;
    return r;
}

