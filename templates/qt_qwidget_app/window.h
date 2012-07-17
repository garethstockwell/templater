#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui/QWidget>

class Window : public QWidget
{
    Q_OBJECT
public:
    Window();
    ~Window();
    void paintEvent(QPaintEvent *event);
};

#endif // WINDOW_H

