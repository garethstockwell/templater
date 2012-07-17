#include "trace.h"
#include "window.h"
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

Window::Window()
{
    qtTrace() << "Window::Window" << qtThisPtr();
}

Window::~Window()
{
    qtTrace() << "Window::~Window" << qtThisPtr();
}

void Window::paintEvent(QPaintEvent *event)
{
    qtVerboseTrace() << "Window::paintEvent" << qtThisPtr() << "rect" << event->rect();
    QPainter painter(this);
    painter.fillRect(event->rect(), Qt::white);
}

