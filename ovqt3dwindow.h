#ifndef OVQT3DWINDOW_H
#define OVQT3DWINDOW_H

#include <iostream>
#include <QGuiApplication>
#include <QKeyEvent>
#include "qt3dwindow.h"

class OvQt3DWindow : public Qt3DExtras::Qt3DWindow
{
    Q_OBJECT
public:
    explicit OvQt3DWindow(QGuiApplication *app);

    int number;

    int Player_Controll;
    int Player_Accelerate;
    int Player_Shoot;
    int Player_MouseX;
    int Player_MouseY;

protected:
    QGuiApplication *app;
    Qt::WindowState Windowstate_Old;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent* event);

signals:

};

#endif // OVQT3DWINDOW_H
