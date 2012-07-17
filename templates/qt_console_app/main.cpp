#include "trace.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtCore/QTimer>

class Application : public QCoreApplication
{
    Q_OBJECT
public:
    Application(int argc, char **argv);
    ~Application();

private slots:
    void run();
};

Application::Application(int argc, char **argv)
    : QCoreApplication(argc, argv)
{
    qtTrace() << "Application::Application" << qtThisPtr()
              << "command line" << arguments().join(" ");
    QTimer::singleShot(0, this, SLOT(run()));
}

Application::~Application()
{
    qtTrace() << "Application::~Application" << qtThisPtr();
}

void Application::run()
{
    qtTrace() << "Application::run" << qtThisPtr();
    // App logic goes here
    quit();
}

int main(int argc, char **argv)
{
    Application app(argc, argv);
    const int r = app.exec();
    qtTrace() << "app.exec() returned" << r;
    return r;
}

#include "main.moc"

